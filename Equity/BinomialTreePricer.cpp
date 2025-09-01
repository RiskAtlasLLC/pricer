// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    BinomialTreePricer.cpp
// Author:  Saurabh Chitnis
// Created: 2025-08-28
// Updated: 2025-08-30
//
// Description:
//   Price american options using binomial tree (Implementation)
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


// import libraries
# include "BinomialTreePricer.hpp"
# include <stdexcept>
# include <vector>

// class BinomicalTreePricer member function implementations
// ----------------------------------------------------------

// constructor with arg
BinomialTreePricer::BinomialTreePricer (AmericanOption option_, int N_) : option(option_), N (N_){}


// binomial tree pricer implementation
double BinomialTreePricer::Pricer(double S, double y, double r, double vol) const {


    // argument validity checks
    if (S <= 0.0) throw std::invalid_argument("S must be > 0.0");
    if (y < 0.0) throw std::invalid_argument("div must be >= 0.0");
    if (vol < 0.0) throw std::invalid_argument("vol must be >= 0.0");
    if (N < 1) throw std::invalid_argument("N must be > 1");

    // parameters needed for pricing
    double dt = (this->option).getT() / static_cast<double> (this->N);
    double disc = std::exp(-r * dt);
    double u = std::exp(vol * std::sqrt(dt));
    double d = 1.0/u ;
    double a = std::exp((r - y) * dt) ;
    double p = (a - d) / (u - d);           // using Cox-Ross-Rubinstein (CRR) binomial model

    // check p for stability
    if (p < 0.0 || p > 1.0 ){

        std::cout << "Fallback to Jarrow-Rudd. p = 0.5" << std::endl;
        
        // fallback to Jarrow–Rudd 
        double m = (r - y - 0.5 * vol * vol) * dt;
        double s = vol * std::sqrt(dt);

        u = std::exp(m + s);
        d = std::exp(m - s);
        p = 0.5;     
    }

    // lattice creation
    std::vector<std::vector<double>> stocktree (this->N+1, std::vector<double>(this->N+1, 0.0));    // stock lattice
    std::vector<std::vector<double>> optiontree (this->N+1, std::vector<double>(this->N+1, 0.0));   // option lattice

    // build stock tree
    stocktree[0][0] = S;
    for (int j = 1; j <= this->N; j++){
        stocktree[j][0] = stocktree[j-1][0] * d ;
        
        for (int i = 1; i <= j; i++){
            stocktree[j][i] = stocktree[j-1][i-1] * u;
        }
    }

    // payoff funciton declare
    std::function<double (const double)> payoff;

    // set  payoff function
    if (option.getAmOptionType() == AmericanOption::AmOptionType::ACall){
        payoff = [&] (const double S) -> double {return std::max(S - option.getK(), 0.0);};
    }
    else{
        payoff = [&] (const double S) -> double {return std::max(option.getK() -  S, 0.0);};
    }

    // payoff at terminal
    for (int i = 0; i <= this->N; i++){
        optiontree[this->N][i] = payoff(stocktree[this->N][i]);
    }

    // backward induction
    for (int i = this->N-1; i >= 0; i--){
        for (int j = 0; j <= i; j++){
            
            double hold = disc * (p * optiontree[i+1][j+1] + (1-p) * optiontree[i+1][j]) ;   // price of am option if held till a later time
            double earlyex = payoff(stocktree[i][j]) ;          // price of am option if excercised early 

            optiontree[i][j] = std::max(hold, earlyex) ;   // am option value is max of value if early excercised and held till a later time 

        }
    }

    return optiontree[0][0] ;

}

// delta calculate
double BinomialTreePricer::delta(double S, double y, double r, double vol) const {

    double delta_S = 0.001 * S ;   
    double Sp = S + delta_S;
    double Sm = std::max(S - delta_S, 1e-12);

    double Vp = Pricer(Sp, y, r, vol);
    double Vm = Pricer(Sm, y, r, vol);

    double delta = (Vp - Vm) / (2 * delta_S) ;

    return delta;
}


// gamma calculate
double BinomialTreePricer::gamma(double S, double y, double r, double vol) const {

    double delta_S = 0.001 * S ;   
    double Sp = S + delta_S;
    double Sm = std::max(S - delta_S, 1e-12);

    double Vp = Pricer(Sp, y, r, vol);
    double Vm = Pricer(Sm, y, r, vol);
    double V0 = Pricer(S, y, r, vol);

    double gamma = (Vp - 2*V0 + Vm) / (delta_S * delta_S) ;

    return gamma;
}


// vega calculate
double BinomialTreePricer::vega(double S, double y, double r, double vol) const {

    double delta_vol = 0.01;   
    double volp = vol + delta_vol;
    double volm = std::max(vol - delta_vol, 0.0);

    double Vp = Pricer(S, y, r, volp);
    double Vm = Pricer(S, y, r, volm);

    double vega = (Vp - Vm) / (2 * delta_vol) ;

    return vega;
}



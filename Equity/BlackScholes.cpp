// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    BlackScholes.cpp
// Author:  Saurabh Chitnis
// Created: 2025-08-26
// Updated: 2025-08-26
//
// Description:
//   Implmentation Black Scholes Pricer
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


// import dependencies
# include "BlackScholes.hpp"
# include <cmath>
#include <boost/math/distributions/normal.hpp>

// constructor with arg : blackscholes
BlackScholesPricer::BlackScholesPricer(EuropeanOption op) : option(op){}

// implement pricer
double BlackScholesPricer::Pricer(double S, double y, double r, double vol) const {

    double price;

    double d1 = ( ( std::log (S / option.getK() ))  + (( r - y + 0.5 * vol * vol ) * option.getT() ) ) / (vol * std::sqrt(option.getT () ) );       // calculate d1

    double d2 = d1 - std::sqrt(option.getT()) * vol;            // calculate d2

    boost::math::normal_distribution<> standard_normal;         // create normal distribution object

    if (option.getEurOptionType() == EuropeanOption::EurOptionType::ECall){
        double N_d1 = boost::math::cdf(standard_normal, d1);        // calculate N_d1
        double N_d2 = boost::math::cdf(standard_normal, d2);        // calculate N_d2

        price = S * std::exp(-y * option.getT()) * N_d1 - (option.getK()) * std::exp(- r * option.getT()) * N_d2;   // calculate call option price using BSM
         
    }
    else{
        double N_md1 = boost::math::cdf(standard_normal, -d1);        // calculate N_d1
        double N_md2 = boost::math::cdf(standard_normal, -d2);        // calculate N_d2

        price = (option.getK()) * std::exp(- r * option.getT()) * N_md2 - S * std::exp(-y * option.getT())  * N_md1;   // calculate put option price using BSM
    }
    
    return price;

}

// implement delta of european option
double BlackScholesPricer::delta(double S, double y, double r, double vol) const {

    double delta;

    double d1 = ( ( std::log (S / option.getK() ))  + (( r - y + 0.5 * vol * vol ) * option.getT() ) ) / (vol * std::sqrt(option.getT () ) );       // calculate d1

    boost::math::normal_distribution<> standard_normal;         // create normal distribution object

    if (option.getEurOptionType() == EuropeanOption::EurOptionType::ECall){
        double N_d1 = boost::math::cdf(standard_normal, d1);        // calculate N_d1
        
        delta = std::exp(-y * option.getT()) * N_d1;
         
    }
    else{
        double N_md1 = boost::math::cdf(standard_normal, -d1);        // calculate N_d1

        delta = -std::exp(-y * option.getT()) * N_md1;
        
    }

    return delta;
}


// implement gamma of european option
double BlackScholesPricer::gamma(double S, double y, double r, double vol) const {

    double gamma;

    double d1 = ( ( std::log (S / option.getK() ))  + (( r - y + 0.5 * vol * vol ) * option.getT() ) ) / (vol * std::sqrt(option.getT () ) );       // calculate d1

    boost::math::normal_distribution<> standard_normal;         // create normal distribution object

    gamma = ( std::exp(-y * option.getT()) * boost::math::pdf(standard_normal, d1)) / ( S * vol * std::sqrt(option.getT()) );

    return gamma;
}


// implement vega of european option
double BlackScholesPricer::vega(double S, double y, double r, double vol) const {

    double vega;

    double d1 = ( ( std::log (S / option.getK() ))  + (( r - y + 0.5 * vol * vol ) * option.getT() ) ) / (vol * std::sqrt(option.getT () ) );       // calculate d1

    boost::math::normal_distribution<> standard_normal;         // create normal distribution object

    vega = ( S * std::exp(-y * option.getT()) * std::sqrt(option.getT()) * boost::math::pdf(standard_normal, d1)) ;

    return vega;
}


//  assumptions in the black scholes model

void BlackScholesPricer::assumptions() const noexcept {
    
    std::cout << "\nAssumptions of the Black Schooes Model"<< std::endl;
    std::cout << "1. Lognormal prices with constant" << std::endl;
    std::cout << "2. Constant r and y (div yield)" << std::endl;
    std::cout << "3. No arbitrage, frictionless markets" << std::endl;
    std::cout << "4. European exercise (no early exercise" << std::endl;
    std::cout << "\n";

}
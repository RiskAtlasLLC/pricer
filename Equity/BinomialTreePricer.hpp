// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    BinomialTreePricer.hpp
// Author:  Saurabh Chitnis
// Created: 2025-08-28
// Updated: 2025-09-04
//
// Description:
//   Price american options using binomial tree (Declaration)
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================

# ifndef BTP_HPP
# define BTP_HPP

// import dependencies
# include "AmericanOption.hpp"

// class BinomialTree

class BinomialTreePricer {

    private:
        AmericanOption option;   // american option
        int N;  // size of the grid
    
    public:
        BinomialTreePricer () = default;       // default constructor
        BinomialTreePricer (AmericanOption, int) ;    // constructor with arg

        ~BinomialTreePricer () = default;      // destructor

        double Pricer (double S, double y, double r, double vol) const;   // generate price of option

        double delta (double S, double y, double r, double vol) const;   // calculate delta of the option

        double gamma(double S, double y, double r, double vol) const;    // calculate gamma of the option

        double vega(double S, double y, double r, double vol) const;    // calculate vega of the option

        // void  assumptions () const noexcept ;    //  prints some assumptions of the black scholes model

};

# endif

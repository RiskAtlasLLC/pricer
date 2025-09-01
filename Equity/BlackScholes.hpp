// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    BlackScholes.hpp
// Author:  Saurabh Chitnis
// Created: 2025-08-26
// Updated: 2025-08-26
//
// Description:
//   Price european options using black scholes model
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================

# ifndef BSM_HPP
# define BSM_HPP

// import dependencies
# include "EuropeanOption.hpp"

// class BlackScholesPricer

class BlackScholesPricer {

    private:
        EuropeanOption option;
    
    public:
        BlackScholesPricer () = delete;       // default constructor
        explicit BlackScholesPricer (EuropeanOption) ;    // constructor with arg

        ~BlackScholesPricer () = default;      // destructor

        double Pricer (double S, double y, double r, double vol) const;   // generate price of option

        double delta (double S, double y, double r, double vol) const;   // calculate delta of the option

        double gamma(double S, double y, double r, double vol) const;    // calculate gamma of the option

        double vega(double S, double y, double r, double vol) const;    // calculate vega of the option

        void  assumptions () const noexcept ;    //  prints some assumptions of the black scholes model

};

# endif

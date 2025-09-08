// ==============================================================
// Company: RiskAtlas LLC
// Project: Price Equity Futures Contract
// File:    FuturePricer.hpp
// Author:  Saurabh Chitnis
// Created: 2025-09-03
// Updated: 2025-09-03
//
// Description:
//   Price equity futures contracts
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================

# ifndef FUTUREPRICER_HPP
# define FUTUREPRICER_HPP

// import dependencies
# include "Futures.hpp"

class FuturePricer {

    private:
        Future f;

    public:
        // constructor no arg
        FuturePricer() = delete;

        // constructor 1 arg
        FuturePricer(Future f_);

        // Pricer
        double Pricer (double S, double y, double r) const;



};




# endif


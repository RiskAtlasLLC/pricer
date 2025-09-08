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


// import dependencies
# include "FuturePricer.hpp"

// pricer constructor
FuturePricer::FuturePricer(Future f_) : f(f_){}

// pricer implementaiton
double FuturePricer::Pricer(double S, double y, double r) const {

    double F = S * std::exp((r - y) * f.getT());
    
    return F - f.get_entryprice().value_or(0.0) ;
}

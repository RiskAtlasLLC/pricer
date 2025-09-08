// ==============================================================
// Company: RiskAtlas LLC
// Project: Futures Fair Price
// File:    Futures.cpp
// Author:  Saurabh Chitnis
// Created: 2025-09-02
// Updated: 2025-09-03
//
// Description:
//   Object for Equity Future with continuous dividend rate
//   A future is an agreement to buy(sell) the underlying at fixed date in the future at a predeterined price
//   
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================

# include "Futures.hpp"

// constructor-1
Future::Future(std::string ticker_, double T_) : underlyingTicker(ticker_), T(T_){
    this->entryprice = std::nullopt;
}

// constructor-2
Future::Future(std::string ticker, double T_ , std::optional<double> entryprice_): underlyingTicker(ticker), T(T_), entryprice(entryprice_){
    
    // check if std::nullopt is passed as an argument
    if (!entryprice_.has_value()){
        std::cout << "Future created, but has no valid entry price. Fill not funciton as intended" << std::endl;
    }
}

// describe the futures contract
void Future::Description() const{
    std::cout << "Futures contract on " << this->underlyingTicker << std::endl;
    std::cout << "Time to expiration " << this->T;
    if (entryprice){
        std::cout << "Entry price of the futures contract : " << entryprice.value() << std::endl;
    }
}

// getters

// returns entry price
std::optional<double> Future::get_entryprice () const noexcept {
    return this->entryprice;
}         

// returns time to maturity
double Future::getT () const noexcept{
    return this->T ;
}        

// returns name of the Ticker
std::string Future::getTicker () const noexcept{
    return this->underlyingTicker ;
}  






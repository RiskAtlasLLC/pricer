// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    EuropeanOption.cpp
// Author:  Saurabh Chitnis
// Created: 2025-08-25
// Updated: 2025-08-25
//
// Description:
//   class EuropeanOption member function implementations
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


// include libraries
# include "EuropeanOption.hpp"

// default constructor
// EuropeanOption::EuropeanOption() {}

// constructor with arg
EuropeanOption::EuropeanOption(EurOptionType type_, std::string underlyingTicker_, double K_, double T_) : 
                                     type(type_), underlyingTicker(underlyingTicker_), K(K_), T(T_){}


// print description
void EuropeanOption::OptionDescription() const {
    
    std::string optype;       // placeholder for type of eur option

    if (type == EurOptionType::ECall){
        optype = "European Call";
    }
    else{
        optype = "European Put";
    }

    std::cout << "\nContract details : " << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Asset: " << optype << " , underlying : " << underlyingTicker << std::endl
            << "strike : " << K << std::endl << "Time to maturity: " << T << "\n" << std::endl;

}


// return strike price of option
double EuropeanOption::getK() const noexcept {

    return this->K;
}

// return time to maturity of option
double EuropeanOption::getT() const noexcept{

    return this->T;
}

// return EurOptionType of the option
EuropeanOption::EurOptionType EuropeanOption::getEurOptionType () const noexcept {

    return this->type; 
}
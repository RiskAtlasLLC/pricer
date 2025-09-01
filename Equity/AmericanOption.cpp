// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    AmericanOption.cpp
// Author:  Saurabh Chitnis
// Created: 2025-08-28
// Updated: 2025-08-28
//
// Description:
//   class AmericanOption member function implementations
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


// include libraries
# include "AmericanOption.hpp"


// constructor with arg
AmericanOption::AmericanOption(AmOptionType type_, std::string underlyingTicker_, double K_, double T_) : 
                                     type(type_), underlyingTicker(underlyingTicker_), K(K_), T(T_){}


// print description
void AmericanOption::OptionDescription() const {
    
    std::string optype;       // placeholder for type of eur option

    if (type == AmOptionType::ACall){
        optype = "American Call";
    }
    else{
        optype = "American Put";
    }

    std::cout << "\nContract details : " << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Asset: " << optype << " , underlying : " << underlyingTicker << std::endl
            << "strike : " << K << std::endl << "Time to maturity: " << T << "\n" << std::endl;

}


// return strike price of option
double AmericanOption::getK() const noexcept {

    return this->K;
}

// return time to maturity of option
double AmericanOption::getT() const noexcept{

    return this->T;
}

// return EurOptionType of the option
AmericanOption::AmOptionType AmericanOption::getAmOptionType () const noexcept {

    return this->type; 
}
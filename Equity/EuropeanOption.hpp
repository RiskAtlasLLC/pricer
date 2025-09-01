// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    EuropeanOption.hpp
// Author:  Saurabh Chitnis
// Created: 2025-08-25
// Updated: 2025-08-25
//
// Description:
//   Object for European Options
//   European options are charaterised by excercise at maturity
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


# ifndef EUROPEANOPTION_HPP
# define EUROPEANOPTION_HPP

// include libraries
# include <string>
# include <iostream>

// EuropeanOption class
class EuropeanOption {

    public:

        enum class EurOptionType {ECall, EPut};  // enumerator for type of option ie Call or Put

    private:
        
        EurOptionType type;     // member variable ie ECall or EPut
        std::string underlyingTicker;   // underlying ticker
        double K;       // option parameters (strike price)
        double T;      // option parameters (timetomaturity)


    public:

        EuropeanOption() = delete;       // default constructor
        EuropeanOption(EurOptionType, std::string, double, double);      // constructor with arg
        
        void OptionDescription () const;      // prints option description (type, strike, timetomaturity)

        double getK () const noexcept ;         // returns strike price
        double getT () const noexcept;         // returns time to maturity
        EurOptionType getEurOptionType () const noexcept;   // return this->type

        ~EuropeanOption() = default;          // destructor

};


# endif
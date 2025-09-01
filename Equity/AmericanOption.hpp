// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    AmericanOption.hpp
// Author:  Saurabh Chitnis
// Created: 2025-08-28
// Updated: 2025-08-28
//
// Description:
//   Object for American Equity Options
//   American options are charaterised by excercise at anytime before maturity
//   
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


# ifndef AMERICANOPTION_HPP
# define AMERICANOPTION_HPP

// include libraries
# include <string>
# include <iostream>

// AmericanOption class
class AmericanOption {

    public:

        enum class AmOptionType {ACall, APut};  // enumerator for type of option ie Call or Put

    private:
        
        AmOptionType type;     // member variable ie ACall or APut
        std::string underlyingTicker;   // underlying ticker
        double K;       // option parameters (strike price)
        double T;      // option parameters (timetomaturity)


    public:

        AmericanOption() = delete;       // default constructor
        AmericanOption(AmOptionType, std::string, double, double);      // constructor with arg
        
        void OptionDescription () const;      // prints option description (type, strike, timetomaturity)

        double getK () const noexcept ;         // returns strike price
        double getT () const noexcept;         // returns time to maturity
        AmOptionType getAmOptionType () const noexcept;   // return this->type

        ~AmericanOption() = default;          // destructor

};


# endif
// ==============================================================
// Company: RiskAtlas LLC
// Project: Futures Fair Price
// File:    Futures.hpp
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

# ifndef EQUITY_FUTURE_HPP
# define EQUITY_FUTURE_HPP

# include <string>
# include <optional>
# include <iostream>

class Future {

    private:

        std::string underlyingTicker;   // underlying ticker
        double T;           // option parameters (timetomaturity)
        std::optional<double> entryprice;       // optional : if a future contract is already entered or not
        
    public:

        // default constructor
        Future() = delete;

        // constructors with arg
        Future(std::string ticker, double T);
        Future(std::string ticker, double T , std::optional<double> entryprice);

        // member funcitons
        void Description () const;      // prints option description (type, strike, timetomaturity)
        std::optional<double> get_entryprice () const noexcept ;         // returns entry price
        double getT () const noexcept;         // returns time to maturity
        std::string getTicker () const noexcept;   // returns name of the Ticker

        ~Future() = default;          // destructor

};

# endif

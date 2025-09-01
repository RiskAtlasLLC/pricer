// ==============================================================
// Company: RiskAtlas LLC
// Project: Black Scholes Model
// File:    main.hpp
// Author:  Saurabh Chitnis
// Created: 2025-08-25
// Updated: 2025-08-30
//
// Description:
//   Test EuropeanOption class
//
// License: Proprietary & Confidential.
//          © 2025 RiskAtlas LLC. All rights reserved.
// ==============================================================


// import dependencies
# include <iostream>
# include "EuropeanOption.hpp"
# include "BlackScholes.hpp"
# include "AmericanOption.hpp"
# include "BinomialTreePricer.hpp"


int main() {

    // set up options
    // --------------
    EuropeanOption op1 (EuropeanOption::EurOptionType::ECall, "AAPL", 213.0, 1);   // create Eur option AAPL Call 213 0.85
    //op1.OptionDescription();   // Descibe option
    BlackScholesPricer bs1 (op1);  // create blackscholes pricer

    EuropeanOption op2 (EuropeanOption::EurOptionType::EPut, "AAPL", 213.0, 1);   // create Eur option AAPL Put 213 0.85
    //op2.OptionDescription();   // Descibe option
    BlackScholesPricer bs2 (op2);  // create blackscholes pricer


    AmericanOption op3 (AmericanOption::AmOptionType::ACall, "AAPL", 213.0, 1);   // create Am option AAPL Call 213 0.85
    //op2.OptionDescription();   // Descibe option
    BinomialTreePricer bt1 (op3, 1000);  // create binomialtree pricer
    
    AmericanOption op4 (AmericanOption::AmOptionType::APut, "AAPL", 213.0, 1);   // create Am option AAPL Put 213 0.85
    //op2.OptionDescription();   // Descibe option
    BinomialTreePricer bt2 (op4, 1000);  // create binomialtree pricer
    

    // run pricers
    // ------------
    double price ;
    price = bs1.Pricer(220, 0.01, 0.02, 0.35);      // run black scholes pricer
    std::cout << "\nEur Call Option price (BSM) = " << price << "\n" << std::endl;

    price = bt1.Pricer(220, 0.01, 0.02, 0.35);      // run binomial tree pricer
    std::cout << "American Call Option price (BT) = " << price << "\n" << std::endl;

    price = bs2.Pricer(220, 0.01, 0.02, 0.35);      // run black scholes pricer
    std::cout << "Eur Put Option price (BSM) = " << price << "\n" << std::endl;

    price = bt2.Pricer(220, 0.01, 0.02, 0.35);      // run binomial tree  pricer
    std::cout << "American Put Option price (BT) = " << price << "\n" << std::endl;


    return 0;

}

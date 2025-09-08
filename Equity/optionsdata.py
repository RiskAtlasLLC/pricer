# ==============================================================
# Company: RiskAtlas LLC
# Project: Option strike data (part of yield curve calibrate)
# File:    optionsdata.py
# Author:  Saurabh Chitnis
# Created: 2025-09-05
# Updated: 2025-09-05
#
# Description:
#   Part of the project to calibrate yield curve using options data.
#   Main purpose is to research on expiry dates of options using yfinance. For the project success, we need to have expiry same across different underlying
#   
#
# License: Proprietary & Confidential.
#          © 2025 RiskAtlas LLC. All rights reserved.
# ==============================================================

# import libraries
import yfinance as yf
import pandas as pd
import numpy as np
from datetime import datetime
import matplotlib.pyplot as plt

# set some tickers
msft = yf.Ticker('MSFT')
nvda = yf.Ticker('NVDA')
aapl = yf.Ticker('AAPL')
spy = yf.Ticker('SPY')
googl = yf.Ticker('GOOGL')

# call option chain for MSFT
msft_call_df = msft.option_chain(msft.options[1]).calls
msft_option = msft.options

#print(msft_call_df[msft_call_df['volume'] > 1000])

#print(msft_call_df)
#print(msft_option)

# we can see ticker.option_chain(ticker.options[i]) to get table for call/puts for that expiry date

# comparing expiry dates across tickers

#print('count mft expiry : ', len(msft.options) )
#print('count appl expiry : ', len(aapl.options) )
#print('count nvda expiry : ', len(nvda.options) )
#print('count spy expiry : ', len(spy.options) )
#print('count googl expiry : ', len(googl.options) )

tickers_list = [msft, aapl, nvda, googl]

# ticker per each expiry
expiry_dates = {}
expiry_dates_list = []

format_date = "%Y-%m-%d"

days_to_exp_list = []

today_date = datetime.strptime('2025-9-5', format_date)


# fill expiry_date{}
for t in tickers_list :
    num_exp = len(t.options)

    for i in range(num_exp) :
        exp = t.options[i]

        if exp not in expiry_dates :
            expiry_dates[exp] = [f'{t.info['longName']}']
            expiry_dates_list.append(exp)

        else :
            expiry_dates[exp].append(f'{t.info['longName']}')

# fill days_to_exp_list
for d in msft.options :

    days_to_exp_list.append(((datetime.strptime(d, format_date) - today_date ).days)/30)
    

# print tickers per each expiry 
#for key, value in expiry_dates.items():
#    print(f"{key}: {value}")


#print(days_to_exp_list)
# Observation
# Upto 2 years of maturity of options,
# treasury par yield curverates availbe 1Mo, 1.5Mo, 2,3,4,6Mo, 1Yr, 2Yr, |3,5,7,10,20,30Yr

# get time to maturity in days (today = 09/05/2025)

# Lets take a look at the volume of these options
# 80 options for each call and put for each maturity

#print(msft.fast_info['lastPrice'])

# setting call and put dictionaries
master_dict = {}

for expdate in range(len(msft.options)) :

    master_dict[msft.options[expdate]] = {'calls' : {}, 'puts' : {} }

    for t in tickers_list :
        # calls
        call_df = t.option_chain(t.options[expdate]).calls
        call_df['mid'] = 0.5 * (call_df['bid'] + call_df['ask'])
        call_df['ba_spread'] = call_df['ask'] - call_df['bid']
        call_df['normalized_ba_spread'] = call_df['ba_spread'] / call_df['mid']
        call_df['moneyness'] = call_df['strike'] / t.fast_info['lastPrice']
        #call_df['tradedtoday'] = (call_df['lastTradeDate'].tz_convert(None) < today_date)
        master_dict[msft.options[expdate]]['calls'][t.info['longName']] = call_df

        # puts
        put_df = t.option_chain(t.options[expdate]).puts
        put_df['mid'] = 0.5 * (put_df['bid'] + put_df['ask'])
        put_df['ba_spread'] = put_df['ask'] - put_df['bid']
        put_df['normalized_ba_spread'] = put_df['ba_spread'] / put_df['mid']
        put_df['moneyness'] = put_df['strike'] / t.fast_info['lastPrice']
        #put_df['tradedtoday'] = (put_df['lastTradeDate'].tz_convert(None) < today_date)
        master_dict[msft.options[expdate]]['puts'][t.info['longName']] = put_df


# access the master_dict
longnames = [msft.info['longName'], aapl.info['longName'], nvda.info['longName'], googl.info['longName']]
expiry_dates_list

# plot volumes for msft by moneyness
def volume_plot(t) :
    for key,values in master_dict.items():
        call_df = master_dict[key]['calls'][t.info['longName']]
        put_df = master_dict[key]['puts'][t.info['longName']]
        plt.plot(call_df['moneyness'], call_df['volume'], 'o', label = 'call', color='purple')
        plt.plot(put_df['moneyness'], put_df['volume'],  'o', label = 'put', color='orange')
        plt.legend()
        plt.title(f'{key}')
        plt.show()



# plot mid prices
def midprice_plot(t) :
    for key,values in master_dict.items():
        call_df = master_dict[key]['calls'][t.info['longName']]
        put_df = master_dict[key]['puts'][t.info['longName']]
        plt.plot(call_df['moneyness'], call_df['mid'], '-', label = 'call', color='purple')
        plt.plot(put_df['moneyness'], put_df['mid'],  '-', label = 'put', color='orange')
        plt.legend()
        plt.title(f'{key}')
        plt.show()

# bid - ask spread 
def normalisedba_plot(t) :
    for key,values in master_dict.items():
        call_df = master_dict[key]['calls'][msft.info['longName']]
        put_df = master_dict[key]['puts'][msft.info['longName']]
        plt.plot(call_df['moneyness'], call_df['normalized_ba_spread'], '-', label = 'call', color='purple')
        plt.plot(put_df['moneyness'], put_df['normalized_ba_spread'],  '-', label = 'put', color='orange')
        plt.legend()
        plt.title(f'{key}')
        plt.show()

normalisedba_plot(nvda)




        
        



















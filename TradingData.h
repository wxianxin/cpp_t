// tick data, c++ 11

#ifndef TRADINGDATA_H_
#define TRADINGDATA_H_

#include <iostream>
#include <map>
#include <random>
#include <string>

#include "TickerData.h"

class TradingData {
   public:
    std::map<std::string, TickerData> ticker_list;
    TradingData(int num);
    ~TradingData();
    void generateRandomData(float mean, float sigma);
    void print_ticker();
    // TradingData getWeightedAverage(int numOfSeconds);

   private:
    int numTicker;
    int* p_;  // pointer to the start of array memory
    int**
        ptr_;  // pointer to the array of pointers, which point to the start of each row
};

#endif
// tick data, c++ 11

#ifndef TICKERDATA_H_
#define TICKERDATA_H_

#include <iostream>
#include <map>
#include <random>
#include <string>

#include "constants.h"

struct Values {
    long long int tick;
    int bidSize, askSize;
    float bid, ask;
};

typedef struct Values Struct;

class TickerData {
   public:
    int**
        ptr;  // pointer to the array of pointers, which point to the start of each row
    TickerData();
    ~TickerData();
    TickerData getWeightedAverage(int numOfSeconds);
    Struct getValues(long long int tickTimeStamp);
    void print_ticker_head(int numOfRows);
    void print_ticker_tail(int numOfRows);

   private:
    int* p_;  // pointer to the start of array memory
    friend class TradingData;
};

#endif
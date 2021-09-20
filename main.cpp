// Steven Wang, 2021 Sept

// Key Notes:
// 1. Everything is saved as int (or long long for Epoch Timestamp with Millisecond).
// 		a. To get correct price, the saved value needs to be devided by 10000.0
// and cast to float.
//      b. To get correct Epoch timestamp, the saved value needs to be converted.
// 2. Did not complete the task of generating 5000 Tickers due to limited memory handling. Here is
// using 100 tickers for an example.
// 3. TradingData is the collection of all the tickers, each ticker has one TickerData
// 4. TickerData is the collection of all the trading data for one ticker.

#include <iostream>
#include <string>

#include "TickerData.h"
#include "TradingData.h"

int main() {
    TradingData myData = TradingData(100);

    // Generate Randon Data
    myData.generateRandomData(0, 0.1);   // mean = 0, sigma = 0.1, distribution of random variable
    Struct values = myData.ticker_list["S0001"].getValues(TIMESTAMP_START + 100 * 5);
    std::cout << "Tick Timestamp: " << values.tick << ", Tick bid: " << values.bid
              << ", Tick ask:" << values.ask << ", Tick bidSize:" << values.bidSize
              << ", Tick askSize:" << values.askSize << std::endl;
    myData.ticker_list["S0001"].print_ticker_head(5);
    myData.ticker_list["S0001"].print_ticker_tail(5);

    // Get Weighted Average
    TickerData myTicker = myData.ticker_list["S0001"].getWeightedAverage(10);
    myTicker.print_ticker_head(5);
    myTicker.print_ticker_tail(5);

    return 0;
}

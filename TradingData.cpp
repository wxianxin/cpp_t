// tick data

#include "TradingData.h"

#include "TickerData.h"

TradingData::TradingData(int num) {
    std::map<std::string, TickerData> ticker_list;

    this->numTicker = num;
    for (int i = 1; i <= num; i++) {
        std::string ticker = "S" + std::to_string(10000 + i).substr(1, 4);
        ticker_list.insert(std::pair<std::string, TickerData>(ticker, TickerData()));
    }
    this->ticker_list = ticker_list;
}

void TradingData::generateRandomData(float mean, float sigma) {
    // Stock Price Drift Wiener Process
    std::random_device randomDevice;
    std::mt19937 seedWiener(randomDevice());
    std::normal_distribution<> normal(mean, sigma);

    // Starting Stock Price of the day
    std::mt19937 seedStock(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> uniform10000(
        1, 10000);  // uniform distribution in range [1, 10000]

    // Liquidity
    std::mt19937 seedLiquidity(randomDevice());
    std::uniform_int_distribution<std::mt19937::result_type> uniform1000(
        1, 1000);  // uniform distribution in range [1, 1000]

    for (int i = 1; i <= this->numTicker; i++) {
        std::string ticker = "S" + std::to_string(10000 + i).substr(1, 4);
        float randomS = uniform10000(seedStock);
        float bidAskSpread =
            randomS * LEVEL_OF_LIQUIDITY * (1000 - uniform1000(seedLiquidity)) / 1000.0;

        for (int c = 0; c < N; c++) {
            // Drift Model: $dS_t = \mu (S_t, t) dt + \sigma (S_t, t) dW_t $
            // => dSt = µStdt + σStdWt
            float arrivalPrice = randomS +=
                MIU * randomS * DELTA_T +
                SIGMA * SQRT_DELTA_T * randomS * normal(seedWiener);
            this->ticker_list[ticker].ptr[c][1] = int(arrivalPrice * 1e4);  // Bid Price
            this->ticker_list[ticker].ptr[c][2] =
                int((arrivalPrice - bidAskSpread) * 1e4);  // Ask Price
            this->ticker_list[ticker].ptr[c][3] =
                uniform1000(seedLiquidity);  // Bid Size
            this->ticker_list[ticker].ptr[c][4] =
                uniform1000(seedLiquidity);  // Ask Size
        }

    }
}

TradingData::~TradingData() {
    for (int i = 1; i <= this->numTicker; i++) {
        std::string ticker = "S" + std::to_string(10000 + i).substr(1, 4);
        this->ticker_list[ticker].~TickerData();
    }
}

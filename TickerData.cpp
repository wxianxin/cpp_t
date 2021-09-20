// tick data

#include "TickerData.h"

TickerData::TickerData() {
    // The idea here is for memory efficiency, allocate an entire chunk of memory
    // beforehand and use pointer to access different cells.
    this->p_ = new int[N * 5];
    this->ptr = new int*[N];

    int j = 0;
    for (int c = 0; c < N * 5; c++) {
        if (c % 5 == 0) {
            this->ptr[j++] = &(this->p_[c]);
            this->p_[c] =
                j - 1;  // time increment, int is not long enough to save epoch
                        // timestamp with milliseconds. The exact timestamp of the this
                        // tick will need to be converted to proper epoch time later.
        } else {
            this->p_[c] = 0;  // initialize bid, ask, bidSize, askSize to be 0
        }
    }
}

TickerData TickerData::getWeightedAverage(int numOfSeconds) {
    TickerData rawTickerData = TickerData();
    int blockSize = 10 * numOfSeconds;

    for (int i = 1; i <= 4; i++) {
        // Get the first moving average
        float temp = 0.0;
        for (int c = 0; c < blockSize; c++) {
            temp += this->ptr[c][i];
        }

        rawTickerData.ptr[0][i] = int(temp / blockSize);

        // Iterate through the rest
        for (int c = 1; c < N - blockSize; c++) {
            rawTickerData.ptr[c][i] =
                rawTickerData.ptr[c - 1][i] +
                (this->ptr[c + blockSize - 1][i] - this->ptr[c - 1][i]) / (blockSize);
        }
    }

    return rawTickerData;
}

void TickerData::print_ticker_head(int numOfRows) {
    std::cout << "=======================================================" << std::endl;

    if (numOfRows > N) {
        numOfRows = N;
    }

    for (int i = 0; i <= numOfRows; i++) {
        std::cout << "tick: " << this->ptr[i][0]
                  << ", bid: " << this->ptr[i][1] / 10000.0
                  << ", ask: " << this->ptr[i][2] / 10000.0
                  << ", bidSize: " << this->ptr[i][3]
                  << ", askSize: " << this->ptr[i][4] << std::endl;
    }
}

void TickerData::print_ticker_tail(int numOfRows) {
    std::cout << "=======================================================" << std::endl;

    int start = N - numOfRows;

    if (start < 0) {
        start = 0;
    }

    for (int i = start; i < N; i++) {
        std::cout << "tick: " << this->ptr[i][0]
                  << ", bid: " << this->ptr[i][1] / 10000.0
                  << ", ask: " << this->ptr[i][2] / 10000.0
                  << ", bidSize: " << this->ptr[i][3]
                  << ", askSize: " << this->ptr[i][4] << std::endl;
    }
}

Struct TickerData::getValues(long long int tickTimeStamp) {
    int tick = (tickTimeStamp - TIMESTAMP_START) / 100;
    Struct values;
    values.tick = TIMESTAMP_START + this->ptr[tick][0] * 100;
    values.bid = this->ptr[tick][1] / 10000.0;
    values.ask = this->ptr[tick][2] / 10000.0;
    values.bidSize = this->ptr[tick][3];
    values.askSize = this->ptr[tick][4];

    return values;
}

TickerData::~TickerData() {
    // delete[] this->p_;
    // delete[] this->ptr;
}
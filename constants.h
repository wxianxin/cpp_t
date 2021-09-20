const long long TIMESTAMP_START = 1632130200000;  // 20210920
const int N = 6.5 * 3600 * 10;
const float MIU = 0.05;   // Mean of Stochastic Model
const float SIGMA = 0.1;  // Standard Deviation of Stochastic Model
const float DELTA_T = 1 / 10 / 3600 / 6.5 /
                      253;  // Time Increment in the unit of year with 253 trading days
const float SQRT_DELTA_T = 0.00013;      // Square Root of DELTA_T
const float LEVEL_OF_LIQUIDITY = 0.005;  // The maximum of Bid/Ask spread in percentage
                                         // of underlying stock price, 0.5%
#pragma once
#include <queue>
#include <deque>
#include <string>
#include <iostream>

struct EnergyReading {
    std::string deviceId;
    double timestamp;
    double usage;
};

class EnergyQueue {
private:
    std::queue<EnergyReading> dataStream;
    std::deque<double> slidingWindow;
    size_t windowSize;

public:
    EnergyQueue(size_t wSize = 10);
    void pushReading(const std::string& id, double time, double usage);
    double processAndGetAverage();
    void predictTrend() const;
    bool isEmpty() const;
};

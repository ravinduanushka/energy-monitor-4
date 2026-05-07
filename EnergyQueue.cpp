#include "EnergyQueue.h"
#include "UndoStack.h"


EnergyQueue::EnergyQueue(size_t wSize) : windowSize(wSize) {}

void EnergyQueue::pushReading(const std::string& id, double time, double usage) {
    dataStream.push({id, time, usage});
}

double EnergyQueue::processAndGetAverage() {
    double totalUsageThisSecond = 0;
    while (!dataStream.empty()) {
        totalUsageThisSecond += dataStream.front().usage;
        dataStream.pop();
    }
    
    if (slidingWindow.size() >= windowSize) {
        slidingWindow.pop_front();
    }
    slidingWindow.push_back(totalUsageThisSecond);
    
    double sum = 0;
    for (double val : slidingWindow) sum += val;
    return slidingWindow.empty() ? 0 : sum / slidingWindow.size();
}

void EnergyQueue::predictTrend() const {
    if (slidingWindow.size() < 2) {
        std::cout << "Not enough data for trend analysis.\n";
        return;
    }
    double firstHalf = 0, secondHalf = 0;
    int half = slidingWindow.size() / 2;
    for (int i = 0; i < slidingWindow.size(); ++i) {
        if (i < half) firstHalf += slidingWindow[i];
        else secondHalf += slidingWindow[i];
    }
    
    std::cout << "--- Predictive Trend Analysis ---\n";
    if (secondHalf > firstHalf * 1.1) std::cout << "UPWARDS\n";
    else if (secondHalf < firstHalf * 0.9) std::cout << "DOWNWARDS\n";
    else std::cout << "STABLE\n";
}

bool EnergyQueue::isEmpty() const {
    return dataStream.empty();
}



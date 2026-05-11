#include "BubbleSort.h"
#include <algorithm>

void bubbleSortDevices(std::vector<Device>& devices) {
    int n = devices.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Sort by power consumption (Highest to Lowest)
            if (devices[j].getPower() < devices[j + 1].getPower()) {
                std::swap(devices[j], devices[j + 1]);
            }
        }
    }
}

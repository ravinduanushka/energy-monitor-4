#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include "EnergyQueue.h"

// Sorts energy readings by usage using Merge Sort (Divide and Conquer)
void mergeSortReadings(std::vector<EnergyReading>& readings, int left, int right);

#endif

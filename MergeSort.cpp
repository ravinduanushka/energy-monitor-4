#include "MergeSort.h"

void merge(std::vector<EnergyReading>& readings, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<EnergyReading> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = readings[left + i];
    for (int j = 0; j < n2; j++) R[j] = readings[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        // Sort by usage (Highest to Lowest)
        if (L[i].usage >= R[j].usage) {
            readings[k] = L[i];
            i++;
        } else {
            readings[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        readings[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        readings[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortReadings(std::vector<EnergyReading>& readings, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortReadings(readings, left, mid);
        mergeSortReadings(readings, mid + 1, right);

        merge(readings, left, mid, right);
    }
}

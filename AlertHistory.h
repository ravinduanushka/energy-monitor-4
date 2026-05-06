#pragma once
#include <list>
#include <string>
#include <iostream>

class AlertHistory {
private:
    std::list<std::string> alerts;
    size_t maxAlerts;

public:
    AlertHistory(size_t limit = 5);
    void addAlert(const std::string& msg);
    void displayAlerts() const;
};
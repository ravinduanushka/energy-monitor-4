#include "AlertHistory.h"

AlertHistory::AlertHistory(size_t limit) : maxAlerts(limit) {}

void AlertHistory::addAlert(const std::string& msg) {
    alerts.push_front(msg);
    if (alerts.size() > maxAlerts) {
        alerts.pop_back();
    }
}

void AlertHistory::displayAlerts() const {
    std::cout << "--- Recent Alerts (Linked List) ---\n";
    for (const auto& alert : alerts) {
        std::cout << "⚠️ " << alert << "\n";
    }
}
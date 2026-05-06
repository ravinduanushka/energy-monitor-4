#pragma once
#include <stack>
#include <string>
#include <iostream>

class UndoStack {
private:
    std::stack<std::string> history;

public:
    void pushAction(const std::string& deviceId);
    std::string popAction();
    bool isEmpty() const;
};
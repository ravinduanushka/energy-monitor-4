#pragma once
#include <stack>
#include <string>
#include <iostream>

class UndoStack {
private:
    std::stack<std::string> history;

public:
    void push(const std::string& action);
    std::string pop();
    bool isEmpty() const;
};
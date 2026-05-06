#pragma once
#include <stack>
#include <iostream>
using namespace std;

class UndoStack {
private:
    stack<string> history;

public:
    void push( string action);
    string pop();
    bool isEmpty() ;
};
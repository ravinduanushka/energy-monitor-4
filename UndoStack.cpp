#include "UndoStack.h"

void UndoStack::push(string action) {
    history.push(action);
}

string UndoStack::pop() {
    if (history.empty()) return "";

    string last = history.top();
    history.pop();
    return last;
}

bool UndoStack::isEmpty()  {
    return history.empty();
}

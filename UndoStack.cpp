#include "UndoStack.h"

void UndoStack::push(const std::string& action) {
    history.push(action);
}

std::string UndoStack::pop() {
    if (history.empty()) return "";
    std::string lastAction = history.top();
    history.pop();
    return lastAction;
}

bool UndoStack::isEmpty() const {
    return history.empty();
}

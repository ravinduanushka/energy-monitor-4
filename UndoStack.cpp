#include "UndoStack.h"

void UndoStack::pushAction(const std::string& deviceId) {
    history.push(deviceId);
}

std::string UndoStack::popAction() {
    if (history.empty()) return "";
    std::string lastId = history.top();
    history.pop();
    return lastId;
}

bool UndoStack::isEmpty() const {
    return history.empty();
}

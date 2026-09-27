#include "CommandInvoker.h"
#include "CancelCommand.h"
#include <iostream>

CommandInvoker::CommandInvoker() {}
CommandInvoker::~CommandInvoker() {}

bool CommandInvoker::execute(std::unique_ptr<Command> command) {
    if (!command) {
        std::cout << "  [Invoker] INVALID: null command rejected" << std::endl;
        return false;
    }
    std::cout << "  [Invoker] Executing: " << command->describe() << std::endl;
    if (!command->execute()) {
        std::cout << "  [Invoker] FAILED: " << command->describe() << std::endl;
        return false;   
    }
    history_.push_back(std::move(command));
    return true;
}

bool CommandInvoker::cancel(std::size_t index) {
    if (index >= history_.size()) {
        std::cout << "  [Invoker] INVALID: no command at history position " << index << std::endl;
        return false;
    }
    return execute(std::unique_ptr<Command>(new CancelCommand(history_[index].get())));
}

bool CommandInvoker::cancelLast() {
    if (history_.empty()) {
        std::cout << "  [Invoker] INVALID: history is empty" << std::endl;
        return false;
    }
    return cancel(history_.size() - 1);
}

std::size_t CommandInvoker::historySize() const { return history_.size(); }

void CommandInvoker::printHistory() const {
    std::cout << "  [Invoker] History (" << history_.size() << "):" << std::endl;
    for (std::size_t i = 0; i < history_.size(); ++i) {
        std::cout << "    " << i << ": " << history_[i]->describe()
                  << (history_[i]->isCancelled() ? "  [CANCELLED]" : "") << std::endl;
    }
}

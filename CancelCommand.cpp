#include "CancelCommand.h"
#include <iostream>

CancelCommand::CancelCommand(Command* target) : target_(target) {}
CancelCommand::~CancelCommand() {}

bool CancelCommand::execute() {
    if (target_ == nullptr) { std::cout << "  [Command] INVALID: nothing to cancel" << std::endl; return false; }
    if (executed_) { std::cout << "  [Command] INVALID: already executed" << std::endl; return false; }
    executed_ = target_->undo();
    return executed_;
}

bool CancelCommand::undo() {
    std::cout << "  [Command] INVALID: a cancellation cannot be undone" << std::endl;
    return false;
}

std::string CancelCommand::describe() const {
    return "Cancel: " + (target_ ? target_->describe() : std::string("<nothing>"));
}

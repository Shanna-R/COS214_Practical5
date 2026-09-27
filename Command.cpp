#include "Command.h"

Command::Command() : executed_(false), cancelled_(false) {}
Command::~Command() {}
bool Command::isExecuted() const { return executed_; }
bool Command::isCancelled() const { return cancelled_; }

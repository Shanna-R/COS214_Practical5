#ifndef COMMANDINVOKER_H
#define COMMANDINVOKER_H

#include <cstddef>
#include <memory>
#include <vector>
#include "Command.h"

class CommandInvoker {
public:
    CommandInvoker();
    ~CommandInvoker();

    CommandInvoker(const CommandInvoker&) = delete;
    CommandInvoker& operator=(const CommandInvoker&) = delete;

    bool execute(std::unique_ptr<Command> command);
    bool cancel(std::size_t index);
    bool cancelLast();

    std::size_t historySize() const;
    void printHistory() const;

private:
    std::vector<std::unique_ptr<Command> > history_;
};

#endif

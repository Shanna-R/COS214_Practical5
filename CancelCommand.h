#ifndef CANCELCOMMAND_H
#define CANCELCOMMAND_H

#include "Command.h"

class CancelCommand : public Command {
public:
    explicit CancelCommand(Command* target);
    ~CancelCommand() override;
    bool execute() override;
    bool undo() override;  
    std::string describe() const override;

private:
    Command* target_; 
};

#endif

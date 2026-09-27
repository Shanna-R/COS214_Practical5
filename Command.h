#ifndef COMMAND_H
#define COMMAND_H

#include <string>
class Command {
public:
    Command();
    virtual ~Command();

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    virtual bool execute() = 0;                 
    virtual bool undo() = 0;                    
    virtual std::string describe() const = 0;   

    bool isExecuted() const;
    bool isCancelled() const;

protected:
    bool executed_;
    bool cancelled_;
};

#endif

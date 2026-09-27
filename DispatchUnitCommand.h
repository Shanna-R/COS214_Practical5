#ifndef DISPATCHUNITCOMMAND_H
#define DISPATCHUNITCOMMAND_H

#include "Command.h"

class ResponseComponent;

class DispatchUnitCommand : public Command {
public:
    DispatchUnitCommand(ResponseComponent* unit, int incidentId, const std::string& location);
    ~DispatchUnitCommand() override;
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    ResponseComponent* unit_;
    int incidentId_;
    std::string location_;
};

#endif

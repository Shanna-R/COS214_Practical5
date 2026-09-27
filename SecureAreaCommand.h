#ifndef SECUREAREACOMMAND_H
#define SECUREAREACOMMAND_H

#include "Command.h"

class FacilitiesTeam;

class SecureAreaCommand : public Command {
public:
    SecureAreaCommand(FacilitiesTeam* facilities, int incidentId, const std::string& area);
    ~SecureAreaCommand() override;
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    FacilitiesTeam* facilities_;   
    int incidentId_;
    std::string area_;
};

#endif

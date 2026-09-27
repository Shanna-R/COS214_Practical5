#ifndef EMERGENCYALERTCOMMAND_H
#define EMERGENCYALERTCOMMAND_H

#include "Command.h"

class CommunicationService;

class EmergencyAlertCommand : public Command {
public:
    EmergencyAlertCommand(CommunicationService* comms, int incidentId,
                          const std::string& location, const std::string& message);
    ~EmergencyAlertCommand() override;
    bool execute() override;
    bool undo() override;
    std::string describe() const override;

private:
    CommunicationService* comms_;   
    int incidentId_;
    std::string location_;
    std::string message_;
};

#endif

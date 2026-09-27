#include "EmergencyAlertCommand.h"
#include "CommunicationService.h"
#include <iostream>
#include <sstream>

EmergencyAlertCommand::EmergencyAlertCommand(CommunicationService* comms, int incidentId,
                                             const std::string& location, const std::string& message)
    : comms_(comms), incidentId_(incidentId), location_(location), message_(message) {}
EmergencyAlertCommand::~EmergencyAlertCommand() {}

bool EmergencyAlertCommand::execute() {
    if (comms_ == nullptr) { std::cout << "  [Command] INVALID: no communication service" << std::endl; return false; }
    if (executed_) { std::cout << "  [Command] INVALID: already executed" << std::endl; return false; }
    executed_ = comms_->issueAlert(incidentId_, location_, message_);
    return executed_;
}

bool EmergencyAlertCommand::undo() {
    if (!executed_ || cancelled_) { std::cout << "  [Command] INVALID: nothing to cancel" << std::endl; return false; }
    cancelled_ = comms_->clearAlert(incidentId_, location_);
    return cancelled_;
}

std::string EmergencyAlertCommand::describe() const {
    std::ostringstream out;
    out << "Emergency alert for " << location_ << ": \"" << message_ << "\" (incident #" << incidentId_ << ")";
    return out.str();
}

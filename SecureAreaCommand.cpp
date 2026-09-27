#include "SecureAreaCommand.h"
#include "FacilitiesTeam.h"
#include <iostream>
#include <sstream>

SecureAreaCommand::SecureAreaCommand(FacilitiesTeam* facilities, int incidentId, const std::string& area)
    : facilities_(facilities), incidentId_(incidentId), area_(area) {}
SecureAreaCommand::~SecureAreaCommand() {}

bool SecureAreaCommand::execute() {
    if (facilities_ == nullptr) { std::cout << "  [Command] INVALID: no facilities team" << std::endl; return false; }
    if (executed_) { std::cout << "  [Command] INVALID: already executed" << std::endl; return false; }
    executed_ = facilities_->secureArea(incidentId_, area_);
    return executed_;
}

bool SecureAreaCommand::undo() {
    if (!executed_ || cancelled_) { std::cout << "  [Command] INVALID: nothing to cancel" << std::endl; return false; }
    cancelled_ = facilities_->reopenArea(incidentId_, area_);
    return cancelled_;
}

std::string SecureAreaCommand::describe() const {
    std::ostringstream out;
    out << "Secure " << area_ << " (incident #" << incidentId_ << ")";
    return out.str();
}

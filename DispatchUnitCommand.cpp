#include "DispatchUnitCommand.h"
#include "ResponseComponent.h"
#include <iostream>
#include <sstream>

DispatchUnitCommand::DispatchUnitCommand(ResponseComponent* unit, int incidentId, const std::string& location)
    : unit_(unit), incidentId_(incidentId), location_(location) {}
DispatchUnitCommand::~DispatchUnitCommand() {}

bool DispatchUnitCommand::execute() {
    if (unit_ == nullptr) { std::cout << "  [Command] INVALID: no unit to dispatch" << std::endl; return false; }
    if (executed_) { std::cout << "  [Command] INVALID: already executed" << std::endl; return false; }
    executed_ = unit_->dispatch(incidentId_, location_);
    return executed_;
}

bool DispatchUnitCommand::undo() {
    if (!executed_ || cancelled_) { std::cout << "  [Command] INVALID: nothing to cancel" << std::endl; return false; }
    cancelled_ = unit_->recall();
    return cancelled_;
}

std::string DispatchUnitCommand::describe() const {
    std::ostringstream out;
    out << "Dispatch " << (unit_ ? unit_->getName() : "<no unit>") << " to " << location_
        << " (incident #" << incidentId_ << ")";
    return out.str();
}

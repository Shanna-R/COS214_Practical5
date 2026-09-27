#include "FacilitiesTeam.h"
#include "AccessControl.h"

FacilitiesTeam::FacilitiesTeam(const std::string& name) : ResponseComponent(name), access_(nullptr), secured_() {}
FacilitiesTeam::~FacilitiesTeam() {}
void FacilitiesTeam::setAccessControl(AccessControl* access) { access_ = access; }
ComponentRole FacilitiesTeam::role() const { return ComponentRole::Facilities; }
bool FacilitiesTeam::isSecured(const std::string& area) const { return secured_.count(area) != 0; }

bool FacilitiesTeam::secureArea(int incidentId, const std::string& area) {
    if (area.empty()) { log("INVALID: no area given to secure"); return false; }
    if (access_ == nullptr) { log("INVALID: no access-control system connected"); return false; }
    if (isSecured(area)) { log("INVALID: " + area + " is already secured"); return false; }
    access_->lockArea(area);
    secured_.insert(area);
    log("Secured " + area + ".");
    announce(CampusEvent(EventType::AreaSecured, incidentId, area, getName()));
    return true;
}

bool FacilitiesTeam::reopenArea(int incidentId, const std::string& area) {
    if (access_ == nullptr) { log("INVALID: no access-control system connected"); return false; }
    if (!isSecured(area)) { log("INVALID: " + area + " is not secured, nothing to reopen"); return false; }
    access_->unlockArea(area);
    secured_.erase(area);
    log("Reopened " + area + ".");
    announce(CampusEvent(EventType::AreaReopened, incidentId, area, getName()));
    return true;
}

void FacilitiesTeam::receive(const CampusEvent& e) {
    recordEvent(e);
    switch (e.type) {
        case EventType::UnitDispatched: log("Preparing access route and lifts for " + e.detail + " at " + e.location); break;
        case EventType::UnitRecalled:   log("Access route for " + e.location + " released"); break;
        case EventType::AreaSecured:    log("Noted " + e.location + " is secured"); break;
        case EventType::AreaReopened:   log("Noted " + e.location + " is open again"); break;
        case EventType::AlertIssued:    log("Switching " + e.location + " to emergency lighting/ventilation"); break;
        case EventType::AlertCleared:   log("Restoring normal lighting/ventilation at " + e.location); break;
    }
}

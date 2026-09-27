#include "SecurityTeam.h"

SecurityTeam::SecurityTeam(const std::string& name) : ResponseComponent(name) {}
SecurityTeam::~SecurityTeam() {}
ComponentRole SecurityTeam::role() const { return ComponentRole::Security; }

void SecurityTeam::receive(const CampusEvent& e) {
    recordEvent(e);
    switch (e.type) {
        case EventType::UnitDispatched: log("Escorting/clearing a path for " + e.detail + " at " + e.location); break;
        case EventType::UnitRecalled:   log("Noted: " + e.detail + " has stood down from " + e.location); break;
        case EventType::AreaSecured:    log("Posting guards at the secured area: " + e.location); break;
        case EventType::AreaReopened:   log("Guards released from " + e.location); break;
        case EventType::AlertIssued:    log("Setting up perimeter and crowd control for the alert at " + e.location); break;
        case EventType::AlertCleared:   log("Perimeter at " + e.location + " being stood down"); break;
    }
}

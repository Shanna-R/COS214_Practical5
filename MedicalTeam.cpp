#include "MedicalTeam.h"

MedicalTeam::MedicalTeam(const std::string& name) : ResponseComponent(name) {}
MedicalTeam::~MedicalTeam() {}
ComponentRole MedicalTeam::role() const { return ComponentRole::Medical; }

void MedicalTeam::receive(const CampusEvent& e) {
    recordEvent(e);
    switch (e.type) {
        case EventType::UnitDispatched: log("Putting an ambulance on standby for " + e.location); break;
        case EventType::UnitRecalled:   log("Standby for " + e.location + " no longer needed"); break;
        case EventType::AreaSecured:    log("Noted " + e.location + " is secured; medics wait for security clearance"); break;
        case EventType::AreaReopened:   log("Access to " + e.location + " restored"); break;
        case EventType::AlertIssued:    log("Preparing triage for the alert at " + e.location); break;
        case EventType::AlertCleared:   log("Triage preparations for " + e.location + " stood down"); break;
    }
}

#include "CommunicationService.h"

CommunicationService::CommunicationService(const std::string& name)
    : ResponseComponent(name), activeAlerts_(), messagesSent_(0) {}
CommunicationService::~CommunicationService() {}
ComponentRole CommunicationService::role() const { return ComponentRole::Communication; }
bool CommunicationService::canBeDispatched() const { return false; }
bool CommunicationService::hasActiveAlert(const std::string& location) const { return activeAlerts_.count(location) != 0; }
int CommunicationService::messagesSent() const { return messagesSent_; }

void CommunicationService::send(const std::string& text) {
    ++messagesSent_;
    log("BROADCAST >> " + text);
}

bool CommunicationService::issueAlert(int incidentId, const std::string& location, const std::string& message) {
    if (message.empty() || location.empty()) { log("INVALID: an alert needs a location and a message"); return false; }
    if (hasActiveAlert(location)) { log("INVALID: an alert is already active for " + location); return false; }
    activeAlerts_[location] = message;
    send("ALERT (" + location + "): " + message);
    announce(CampusEvent(EventType::AlertIssued, incidentId, location, message));
    return true;
}

bool CommunicationService::clearAlert(int incidentId, const std::string& location) {
    if (!hasActiveAlert(location)) { log("INVALID: no active alert for " + location + " to clear"); return false; }
    activeAlerts_.erase(location);
    send("ALL CLEAR (" + location + ")");
    announce(CampusEvent(EventType::AlertCleared, incidentId, location, "all clear"));
    return true;
}

void CommunicationService::receive(const CampusEvent& e) {
    recordEvent(e);
    switch (e.type) {
        case EventType::UnitDispatched: send(e.detail + " is responding to " + e.location); break;
        case EventType::UnitRecalled:   send(e.detail + " has stood down at " + e.location); break;
        case EventType::AreaSecured:    send(e.location + " is now restricted - please avoid the area"); break;
        case EventType::AreaReopened:   send(e.location + " has reopened"); break;
        case EventType::AlertIssued:    break;  
        case EventType::AlertCleared:   break;
    }
}

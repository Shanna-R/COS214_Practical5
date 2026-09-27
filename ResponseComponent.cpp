#include "ResponseComponent.h"
#include <iostream>
#include <sstream>

ResponseComponent::ResponseComponent(const std::string& name)
    : name_(name), mediator_(nullptr), deployed_(false), incidentId_(-1), location_(),
      eventsReceived_(0), updatesReceived_(0) {}

ResponseComponent::~ResponseComponent() {}

void ResponseComponent::setMediator(Mediator* mediator) { mediator_ = mediator; }
const std::string& ResponseComponent::getName() const { return name_; }
bool ResponseComponent::isDeployed() const { return deployed_; }
int ResponseComponent::getIncidentId() const { return incidentId_; }
const std::string& ResponseComponent::getLocation() const { return location_; }
int ResponseComponent::eventsReceived() const { return eventsReceived_; }
int ResponseComponent::updatesReceived() const { return updatesReceived_; }
bool ResponseComponent::canBeDispatched() const { return true; }

bool ResponseComponent::dispatch(int incidentId, const std::string& location) {
    if (!canBeDispatched()) {
        log("INVALID: this component is not a dispatchable unit");
        return false;
    }
    if (location.empty()) {
        log("INVALID: cannot dispatch without a location");
        return false;
    }
    if (deployed_) {
        std::ostringstream msg;
        msg << "INVALID: already deployed to " << location_ << " (incident #" << incidentId_ << ")";
        log(msg.str());
        return false;
    }
    deployed_ = true;
    incidentId_ = incidentId;
    location_ = location;
    log("Deployed to " + location + ".");
    announce(CampusEvent(EventType::UnitDispatched, incidentId, location, name_));
    return true;
}

bool ResponseComponent::recall() {
    if (!canBeDispatched() || !deployed_) {
        log("INVALID: nothing to recall");
        return false;
    }
    int id = incidentId_;
    std::string where = location_;
    deployed_ = false;
    incidentId_ = -1;
    location_.clear();
    log("Recalled from " + where + ".");
    announce(CampusEvent(EventType::UnitRecalled, id, where, name_));
    return true;
}

void ResponseComponent::announce(const CampusEvent& event) {
    if (mediator_ == nullptr) {
        log("WARNING: not connected to a mediator, nobody was told about " + toString(event.type));
        return;
    }
    mediator_->notify(this, event);
}

void ResponseComponent::recordEvent(const CampusEvent&) { ++eventsReceived_; }

void ResponseComponent::update(int incidentId, const std::string& status) {
    ++updatesReceived_;
    log("Incident #" + std::to_string(incidentId) + " is now " + status);
}

void ResponseComponent::log(const std::string& message) const {
    std::cout << "    [" << name_ << "] " << message << std::endl;
}

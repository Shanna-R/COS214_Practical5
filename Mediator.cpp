#include "Mediator.h"

CampusEvent::CampusEvent(EventType t, int id, const std::string& loc, const std::string& d)
    : type(t), incidentId(id), location(loc), detail(d) {}

Mediator::~Mediator() {}

std::string toString(EventType t) {
    switch (t) {
        case EventType::UnitDispatched: return "UnitDispatched";
        case EventType::UnitRecalled:   return "UnitRecalled";
        case EventType::AreaSecured:    return "AreaSecured";
        case EventType::AreaReopened:   return "AreaReopened";
        case EventType::AlertIssued:    return "AlertIssued";
        case EventType::AlertCleared:   return "AlertCleared";
    }
    return "Unknown";
}

std::string toString(ComponentRole r) {
    switch (r) {
        case ComponentRole::Security:      return "Security";
        case ComponentRole::Medical:       return "Medical";
        case ComponentRole::Facilities:    return "Facilities";
        case ComponentRole::Communication: return "Communication";
    }
    return "Unknown";
}

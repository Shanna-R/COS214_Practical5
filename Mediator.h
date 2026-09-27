#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <string>

class ResponseComponent;

enum class ComponentRole { Security, Medical, Facilities, Communication };

enum class EventType {
    UnitDispatched,
    UnitRecalled,
    AreaSecured,
    AreaReopened,
    AlertIssued,
    AlertCleared
};

struct CampusEvent {
    EventType type;
    int incidentId;
    std::string location;
    std::string detail;  

    CampusEvent(EventType t, int id, const std::string& loc, const std::string& d = "");
};

std::string toString(EventType t);
std::string toString(ComponentRole r);

class Mediator {
public:
    virtual ~Mediator();
    virtual void registerComponent(ResponseComponent* component) = 0;
    virtual void notify(ResponseComponent* sender, const CampusEvent& event) = 0;
};

#endif

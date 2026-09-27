#include "CampusMediator.h"
#include "ResponseComponent.h"
#include <iostream>

CampusMediator::CampusMediator() {
    routes_[EventType::UnitDispatched] = {ComponentRole::Security, ComponentRole::Medical,
                                          ComponentRole::Facilities, ComponentRole::Communication};
    routes_[EventType::UnitRecalled]   = {ComponentRole::Security, ComponentRole::Medical,
                                          ComponentRole::Facilities, ComponentRole::Communication};
    routes_[EventType::AreaSecured]    = {ComponentRole::Security, ComponentRole::Medical,
                                          ComponentRole::Communication};
    routes_[EventType::AreaReopened]   = {ComponentRole::Security, ComponentRole::Communication};
    routes_[EventType::AlertIssued]    = {ComponentRole::Security, ComponentRole::Medical,
                                          ComponentRole::Facilities};
    routes_[EventType::AlertCleared]   = {ComponentRole::Security, ComponentRole::Medical,
                                          ComponentRole::Facilities};
}

CampusMediator::~CampusMediator() {}

void CampusMediator::registerComponent(ResponseComponent* component) {
    if (component == nullptr) {
        std::cout << "  [Mediator] INVALID: cannot register a null component" << std::endl;
        return;
    }
    if (components_.count(component->role()) != 0) {
        std::cout << "  [Mediator] INVALID: a " << toString(component->role())
                  << " component is already registered" << std::endl;
        return;
    }
    components_[component->role()] = component;
    component->setMediator(this);
    std::cout << "  [Mediator] Registered " << component->getName() << " ("
              << toString(component->role()) << ")" << std::endl;
}

void CampusMediator::notify(ResponseComponent* sender, const CampusEvent& event) {
    std::map<ComponentRole, ResponseComponent*>::const_iterator seat = components_.find(sender->role());
    if (seat == components_.end() || seat->second != sender) {
        std::cout << "  [Mediator] REJECTED " << toString(event.type) << " from unregistered component "
                  << sender->getName() << std::endl;
        return;
    }

    std::map<EventType, std::vector<ComponentRole> >::const_iterator route = routes_.find(event.type);
    if (route == routes_.end()) {
        std::cout << "  [Mediator] No coordination rule for " << toString(event.type) << std::endl;
        return;
    }

    std::cout << "  [Mediator] " << sender->getName() << " reported " << toString(event.type)
              << " at " << event.location << " (incident #" << event.incidentId << ")" << std::endl;

    for (std::size_t i = 0; i < route->second.size(); ++i) {
        std::map<ComponentRole, ResponseComponent*>::const_iterator target = components_.find(route->second[i]);
        if (target == components_.end() || target->second == sender) {
            continue;
        }
        target->second->receive(event);
    }
}

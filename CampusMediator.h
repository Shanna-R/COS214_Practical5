#ifndef CAMPUSMEDIATOR_H
#define CAMPUSMEDIATOR_H

#include <map>
#include <vector>
#include "Mediator.h"

class CampusMediator : public Mediator {
public:
    CampusMediator();
    ~CampusMediator() override;

    void registerComponent(ResponseComponent* component) override;
    void notify(ResponseComponent* sender, const CampusEvent& event) override;

private:
    std::map<ComponentRole, ResponseComponent*> components_;          
    std::map<EventType, std::vector<ComponentRole> > routes_;         
};

#endif

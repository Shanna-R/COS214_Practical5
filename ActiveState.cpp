#include "ActiveState.h"
#include "Incident.h"
#include "ResolvedState.h"

#include <iostream>


void ActiveState::activate(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " is already ACTIVE." << std::endl;
}

void ActiveState::resolve(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " is now RESOLVED." << std::endl;

    incident.setState(new ResolvedState());
}

void ActiveState::cancel(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " has been cancelled." << std::endl;
}

const char* ActiveState::getName() const
{
    return "Active";
}
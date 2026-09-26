#include "ReportedState.h"
#include "Incident.h"
#include "ActiveState.h"

#include <iostream>


void ReportedState::activate(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " is now ACTIVE." << std::endl;

    incident.setState(new ActiveState());
}

void ReportedState::resolve(Incident& incident)
{
    std::cout << "Cannot resolve Incident " << incident.getId() << " because it is still REPORTED." << std::endl;
}

void ReportedState::cancel(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " has been cancelled." << std::endl;
}

const char* ReportedState::getName() const
{
    return "Reported";
}
#include "ResolvedState.h"
#include "Incident.h"

#include <iostream>


void ResolvedState::activate(Incident& incident)
{
    std::cout << "Cannot activate Incident " << incident.getId() << " because it is already RESOLVED." << std::endl;
}

void ResolvedState::resolve(Incident& incident)
{
    std::cout << "Incident " << incident.getId() << " is already RESOLVED." << std::endl;
}

void ResolvedState::cancel(Incident& incident)
{
    std::cout << "Cannot cancel Incident " << incident.getId() << " because it is already RESOLVED." << std::endl;
}

const char* ResolvedState::getName() const
{
    return "Resolved";
}
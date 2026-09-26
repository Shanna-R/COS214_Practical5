#include "Incident.h"
#include "IncidentState.h"
#include "ReportedState.h"
#include "IncidentObserver.h"

#include <iostream>
#include <algorithm>


Incident::Incident( int id, const std::string& type, const std::string& location, const std::string& description)
    : id(id),
      type(type),
      location(location),
      description(description),
      currentState(new ReportedState())
{
}

Incident::~Incident()
{
    delete currentState;
}

int Incident::getId() const
{
    return id;
}

std::string Incident::getType() const
{
    return type;
}

std::string Incident::getLocation() const
{
    return location;
}

std::string Incident::getDescription() const
{
    return description;
}

std::string Incident::getStateName() const
{
    return currentState->getName();
}

void Incident::setState(IncidentState* state)
{
    if(state == nullptr)
    {
        return;
    }

    delete currentState;
    currentState = state;

    notifyObservers();
}

void Incident::activate()
{
    currentState->activate(*this);
}

void Incident::resolve()
{
    currentState->resolve(*this);
}

void Incident::cancel()
{
    currentState->cancel(*this);
}

void Incident::attach(IncidentObserver* observer)
{
    if(observer == nullptr)
    {
        return;
    }

    observers.push_back(observer);
}

void Incident::detach(IncidentObserver* observer)
{
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void Incident::notifyObservers()
{
    for(IncidentObserver* observer : observers)
    {
        if(observer != nullptr)
        {
            observer->update(id, getStateName());
        }
    }
}
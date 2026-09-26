#ifndef INCIDENTOBSERVER_H
#define INCIDENTOBSERVER_H

#include <string>

class IncidentObserver
{
    public:
        virtual ~IncidentObserver() {}
        virtual void update(int incidentId, const std::string& status) = 0;
};

#endif
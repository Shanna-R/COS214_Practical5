#ifndef INCIDENTSTATE_H
#define INCIDENTSTATE_H

class Incident;

class IncidentState
{
    public:
        virtual ~IncidentState() {}
        virtual void activate(Incident& incident) = 0;
        virtual void resolve(Incident& incident) = 0;
        virtual void cancel(Incident& incident) = 0;
        virtual const char* getName() const = 0;
};

#endif
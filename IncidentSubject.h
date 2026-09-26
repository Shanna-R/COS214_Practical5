#ifndef INCIDENTSUBJECT_H
#define INCIDENTSUBJECT_H

class IncidentObserver;

class IncidentSubject
{
public:
        virtual ~IncidentSubject() {}
        virtual void attach(IncidentObserver* observer) = 0;
        virtual void detach(IncidentObserver* observer) = 0;
        virtual void notifyObservers() = 0;
};

#endif
#ifndef INCIDENT_H
#define INCIDENT_H

#include "IncidentSubject.h"

#include <string>
#include <vector>

class IncidentState;
class IncidentObserver;

class Incident : public IncidentSubject
{
    private:
        int id;
        std::string type;
        std::string location;
        std::string description;
        IncidentState* currentState;
        std::vector<IncidentObserver*> observers;

    public:
        Incident(int id, const std::string& type, const std::string& location, const std::string& description);
        ~Incident();
        int getId() const;

        std::string getType() const;
        std::string getLocation() const;
        std::string getDescription() const;
        std::string getStateName() const;

        void setState(IncidentState* state);
        void activate();
        void resolve();
        void cancel();
        void attach(IncidentObserver* observer) override;
        void detach(IncidentObserver* observer) override;
        void notifyObservers() override;
};

#endif
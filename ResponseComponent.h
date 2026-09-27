#ifndef RESPONSECOMPONENT_H
#define RESPONSECOMPONENT_H

#include <string>
#include "Mediator.h"
#include "IncidentObserver.h"
class ResponseComponent : public IncidentObserver {
public:
    explicit ResponseComponent(const std::string& name);
    ~ResponseComponent() override;

    ResponseComponent(const ResponseComponent&) = delete;
    ResponseComponent& operator=(const ResponseComponent&) = delete;

    void setMediator(Mediator* mediator);         
    const std::string& getName() const;
    virtual ComponentRole role() const = 0;

    virtual bool dispatch(int incidentId, const std::string& location);
    virtual bool recall();
    virtual void receive(const CampusEvent& event) = 0;

    void update(int incidentId, const std::string& status) override;

    bool isDeployed() const;
    int getIncidentId() const;
    const std::string& getLocation() const;
    int eventsReceived() const;
    int updatesReceived() const;

protected:
    virtual bool canBeDispatched() const;          
    void announce(const CampusEvent& event);       
    void recordEvent(const CampusEvent& event);    
    void log(const std::string& message) const;

private:
    std::string name_;
    Mediator* mediator_;
    bool deployed_;
    int incidentId_;
    std::string location_;
    int eventsReceived_;
    int updatesReceived_;
};

#endif

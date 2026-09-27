#ifndef COMMUNICATIONSERVICE_H
#define COMMUNICATIONSERVICE_H

#include <map>
#include "ResponseComponent.h"

class CommunicationService : public ResponseComponent {
public:
    explicit CommunicationService(const std::string& name = "Communication Service");
    ~CommunicationService() override;
    ComponentRole role() const override;

    bool issueAlert(int incidentId, const std::string& location, const std::string& message);
    bool clearAlert(int incidentId, const std::string& location);
    bool hasActiveAlert(const std::string& location) const;
    int messagesSent() const;

    void receive(const CampusEvent& event) override;

protected:
    bool canBeDispatched() const override;  

private:
    void send(const std::string& text);
    std::map<std::string, std::string> activeAlerts_;   
    int messagesSent_;
};

#endif

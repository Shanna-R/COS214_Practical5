#ifndef ALERTSERVICE_H
#define ALERTSERVICE_H

#include <string>

class AlertService {
public:
    void sendCampusAlert(const std::string& message);
};

#endif // ALERTSERVICE_H
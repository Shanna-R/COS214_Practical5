#include "AlertService.h"
#include <iostream>

void AlertService::sendCampusAlert(const std::string& message) {
    std::cout << "[AlertService] CAMPUS-WIDE ALERT: " << message << std::endl;
}
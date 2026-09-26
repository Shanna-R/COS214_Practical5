#ifndef BUILDINGACCESSSERVICE_H
#define BUILDINGACCESSSERVICE_H

#include "AccessControl.h"
#include <string>

class BuildingAccessService {
private:
    AccessControl* accessControl;

public:
    explicit BuildingAccessService(AccessControl* accControl);
    void lockBuilding(const std::string& buildingName);
};

#endif // BUILDINGACCESSSERVICE_H
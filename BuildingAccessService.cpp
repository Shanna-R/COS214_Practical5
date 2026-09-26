#include "BuildingAccessService.h"
#include <iostream>

BuildingAccessService::BuildingAccessService(AccessControl* accControl) 
    : accessControl(accControl) {}

void BuildingAccessService::lockBuilding(const std::string& buildingName) {
    std::cout << "[BuildingAccessService] Initiating lock on " << buildingName << std::endl;
    if (accessControl) {
        accessControl->lockArea(buildingName);
    }
}
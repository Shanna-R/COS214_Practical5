#include "EmergencyFacade.h"
#include <iostream>

EmergencyFacade::EmergencyFacade(AccessControl* accessControlAdapter)
    : buildingAccessService(accessControlAdapter) {}

void EmergencyFacade::handleSevereEmergency(const std::string& buildingName, const std::string& emergencyType) {
    std::cout << "\n=== [EmergencyFacade] Executing Severe Emergency Response Protocol ===" << std::endl;
    
    // Step 1: Dispatch emergency services
    dispatchService.dispatchTeam("Security & Medical", buildingName);
    
    // Step 2: Lock affected building (uses Adapter under the hood)
    buildingAccessService.lockBuilding(buildingName);
    
    // Step 3: Broadcast public emergency alert
    alertService.sendCampusAlert("EMERGENCY: " + emergencyType + " detected at " + buildingName + ". Area locked down.");
    
    std::cout << "=== [EmergencyFacade] Protocol Execution Complete ===\n" << std::endl;
}
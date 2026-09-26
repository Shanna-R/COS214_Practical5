#ifndef EMERGENCYFACADE_H
#define EMERGENCYFACADE_H

#include "DispatchService.h"
#include "AlertService.h"
#include "BuildingAccessService.h"
#include <string>

class EmergencyFacade {
private:
    DispatchService dispatchService;
    AlertService alertService;
    BuildingAccessService buildingAccessService;

public:
    explicit EmergencyFacade(AccessControl* accessControlAdapter);
    
    // High-level operation executing 3+ subsystem actions
    void handleSevereEmergency(const std::string& buildingName, const std::string& emergencyType);
};

#endif // EMERGENCYFACADE_H
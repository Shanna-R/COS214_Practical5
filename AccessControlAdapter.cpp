#include "AccessControlAdapter.h"
#include <iostream>

AccessControlAdapter::AccessControlAdapter(LegacyAccessSystem* legacySys)
    : legacySystem(legacySys) {}

int AccessControlAdapter::mapAreaToZoneId(const std::string& areaName) const {
    if (areaName == "Engineering Building") return 17;
    if (areaName == "Science Block") return 42;
    if (areaName == "Main Campus") return 101;
    return 999; // Default unknown zone
}

void AccessControlAdapter::lockArea(const std::string& areaName) {
    int zoneId = mapAreaToZoneId(areaName);
    std::cout << "[Adapter] Mapping '" << areaName << "' -> Zone " << zoneId << std::endl;
    legacySystem->secureZone(zoneId);
}

void AccessControlAdapter::unlockArea(const std::string& areaName) {
    int zoneId = mapAreaToZoneId(areaName);
    std::cout << "[Adapter] Mapping '" << areaName << "' -> Zone " << zoneId << std::endl;
    legacySystem->releaseZone(zoneId);
}
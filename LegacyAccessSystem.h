#ifndef LEGACYACCESSSYSTEM_H
#define LEGACYACCESSSYSTEM_H

#include <iostream>

// Adaptee: Incompatible legacy system using zone IDs (integers)
class LegacyAccessSystem {
public:
    void secureZone(int zoneId) {
        std::cout << "[LegacyAccessSystem] Securing Zone ID: " << zoneId << std::endl;
    }

    void releaseZone(int zoneId) {
        std::cout << "[LegacyAccessSystem] Releasing Zone ID: " << zoneId << std::endl;
    }
};

#endif // LEGACYACCESSSYSTEM_H
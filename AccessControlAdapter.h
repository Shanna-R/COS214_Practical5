#ifndef ACCESSCONTROLADAPTER_H
#define ACCESSCONTROLADAPTER_H

#include "AccessControl.h"
#include "LegacyAccessSystem.h"

// Adapter: Translates string area names to integer zone IDs
class AccessControlAdapter : public AccessControl {
private:
    LegacyAccessSystem* legacySystem;
    int mapAreaToZoneId(const std::string& areaName) const;

public:
    explicit AccessControlAdapter(LegacyAccessSystem* legacySys);
    ~AccessControlAdapter() override = default;

    void lockArea(const std::string& areaName) override;
    void unlockArea(const std::string& areaName) override;
};

#endif // ACCESSCONTROLADAPTER_H
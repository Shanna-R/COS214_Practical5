#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include <string>

// Target Interface expected by CampusGuard
class AccessControl {
public:
    virtual ~AccessControl() = default;
    virtual void lockArea(const std::string& areaName) = 0;
    virtual void unlockArea(const std::string& areaName) = 0;
};

#endif // ACCESSCONTROL_H
#ifndef DISPATCHSERVICE_H
#define DISPATCHSERVICE_H

#include <string>

class DispatchService {
public:
    void dispatchTeam(const std::string& teamType, const std::string& location);
};

#endif // DISPATCHSERVICE_H
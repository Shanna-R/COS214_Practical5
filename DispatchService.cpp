#include "DispatchService.h"
#include <iostream>

void DispatchService::dispatchTeam(const std::string& teamType, const std::string& location) {
    std::cout << "[DispatchService] Dispatched " << teamType << " team to " << location << std::endl;
}
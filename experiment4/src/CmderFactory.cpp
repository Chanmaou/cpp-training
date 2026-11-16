#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string& commands, VehicleType type) const noexcept
{
    const CmderMap* commandMap = &normalMap;
    switch (type) {
    case VehicleType::Normal:
        break;
    case VehicleType::SportsCar:
        commandMap = &sportsCarMap;
        break;
    case VehicleType::Bus:
        commandMap = &busMap;
        break;
    }

    CmderList cmders;
    for (const auto command : ParseCommandString(commands)) {
        const auto it = commandMap->find(command);
        if (it != commandMap->end()) {
            cmders.push_back(it->second);
        }
    }
    return cmders;
}

std::string CmderFactory::ParseCommandString(const std::string& commands) const noexcept
{
    std::string result = commands;
    std::string::size_type pos = 0;
    while ((pos = result.find("TR", pos)) != std::string::npos) {
        result.replace(pos, 2, "Z");
        ++pos;
    }
    return result;
}
}  // namespace adas
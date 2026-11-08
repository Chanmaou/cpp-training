#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept
{
    CmderList cmders;
    for (const auto command : ParseCommandString(commands)) {
        const auto it = cmderMap.find(command);
        if (it != cmderMap.end()) {
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
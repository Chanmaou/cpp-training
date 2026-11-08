#include "CmderFactory.hpp"

namespace adas
{
CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept
{
    CmderList cmders;
    for (const auto command : commands) {
        const auto it = cmderMap.find(command);
        if (it != cmderMap.end()) {
            cmders.push_back(it->second);
        }
    }
    return cmders;
}
}  // namespace adas

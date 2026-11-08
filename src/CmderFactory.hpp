#pragma once

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include "Command.hpp"
#include "TurnRoundCommand.hpp"

namespace adas
{
using Cmder = std::function<ActionGroup(const PoseHandler&)>;
using CmderList = std::list<Cmder>;

class CmderFactory final
{
public:
    CmderFactory() noexcept = default;
    ~CmderFactory() = default;

    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

    CmderList GetCmders(const std::string& commands) const noexcept;

private:
    std::string ParseCommandString(const std::string& commands) const noexcept;

    const std::unordered_map<char, Cmder> cmderMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},  {'Z', TurnRoundCommand()},
    };
};
}  // namespace adas
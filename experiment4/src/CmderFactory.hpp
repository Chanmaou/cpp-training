#pragma once

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include "BusCommand.hpp"
#include "Command.hpp"
#include "Executor.hpp"
#include "SportsCarCommand.hpp"
#include "TurnRoundCommand.hpp"

namespace adas
{
using Cmder = std::function<ActionGroup(const PoseHandler&)>;
using CmderList = std::list<Cmder>;
using CmderMap = std::unordered_map<char, Cmder>;

class CmderFactory final
{
public:
    CmderFactory() noexcept = default;
    ~CmderFactory() = default;

    CmderFactory(const CmderFactory&) = delete;
    CmderFactory& operator=(const CmderFactory&) = delete;

    CmderList GetCmders(const std::string& commands, VehicleType type) const noexcept;

private:
    std::string ParseCommandString(const std::string& commands) const noexcept;

    const CmderMap normalMap{
        {'M', MoveCommand()}, {'L', TurnLeftCommand()}, {'R', TurnRightCommand()},
        {'F', FastCommand()}, {'B', ReverseCommand()},  {'Z', TurnRoundCommand()},
    };

    const CmderMap sportsCarMap{
        {'M', SportsCarMoveCommand()}, {'L', SportsCarTurnLeftCommand()}, {'R', SportsCarTurnRightCommand()},
        {'F', FastCommand()},          {'B', ReverseCommand()},           {'Z', TurnRoundCommand()},
    };

    const CmderMap busMap{
        {'M', MoveCommand()},
        {'L', BusTurnCommand(ActionType::TurnLeft, ActionType::TurnRight)},
        {'R', BusTurnCommand(ActionType::TurnRight, ActionType::TurnLeft)},
        {'F', FastCommand()},
        {'B', ReverseCommand()},
        {'Z', TurnRoundCommand()},
    };
};
}  // namespace adas

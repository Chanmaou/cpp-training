#pragma once

#include "Command.hpp"

namespace adas
{
class BusTurnCommand final
{
public:
    BusTurnCommand(ActionType forwardTurn, ActionType reverseTurn) noexcept
        : forwardTurn(forwardTurn), reverseTurn(reverseTurn)
    {
    }

    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        auto group = MoveCommand{}(poseHandler);
        group.PushAction(poseHandler.IsReverse() ? reverseTurn : forwardTurn);
        return group;
    }

private:
    ActionType forwardTurn;
    ActionType reverseTurn;
};
}  // namespace adas
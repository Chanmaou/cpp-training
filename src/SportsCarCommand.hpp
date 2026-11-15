#pragma once

#include "ActionGroup.hpp"

namespace adas
{
class SportsCarMoveCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
        const int steps = poseHandler.IsFast() ? 4 : 2;
        for (int i = 0; i < steps; ++i) {
            group.PushAction(move);
        }
        return group;
    }
};

class SportsCarTurnLeftCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
        if (poseHandler.IsFast()) {
            group.PushAction(move);
        }
        const auto turn = poseHandler.IsReverse() ? ActionType::TurnRight : ActionType::TurnLeft;
        group.PushAction(turn);
        group.PushAction(move);
        return group;
    }
};

class SportsCarTurnRightCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
        if (poseHandler.IsFast()) {
            group.PushAction(move);
        }
        const auto turn = poseHandler.IsReverse() ? ActionType::TurnLeft : ActionType::TurnRight;
        group.PushAction(turn);
        group.PushAction(move);
        return group;
    }
};
}  // namespace adas
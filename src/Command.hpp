#pragma once

#include "ActionGroup.hpp"

namespace adas
{
class MoveCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
        if (poseHandler.IsFast()) {
            group.PushAction(move);
        }
        group.PushAction(move);
        return group;
    }
};

class TurnLeftCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        if (poseHandler.IsFast()) {
            const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
            group.PushAction(move);
        }
        const auto turn = poseHandler.IsReverse() ? ActionType::TurnRight : ActionType::TurnLeft;
        group.PushAction(turn);
        return group;
    }
};

class TurnRightCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        if (poseHandler.IsFast()) {
            const auto move = poseHandler.IsReverse() ? ActionType::Backward : ActionType::Forward;
            group.PushAction(move);
        }
        const auto turn = poseHandler.IsReverse() ? ActionType::TurnLeft : ActionType::TurnRight;
        group.PushAction(turn);
        return group;
    }
};

class FastCommand final
{
public:
    ActionGroup operator()(const PoseHandler&) const noexcept
    {
        return ActionGroup({ActionType::ToggleFast});
    }
};

class ReverseCommand final
{
public:
    ActionGroup operator()(const PoseHandler&) const noexcept
    {
        return ActionGroup({ActionType::ToggleReverse});
    }
};
}

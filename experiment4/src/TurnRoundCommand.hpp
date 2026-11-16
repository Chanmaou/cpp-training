#pragma once

#include "ActionGroup.hpp"

namespace adas
{
class TurnRoundCommand final
{
public:
    ActionGroup operator()(const PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsReverse()) {
            return ActionGroup();
        }
        ActionGroup group;
        if (poseHandler.IsFast()) {
            group.PushAction(ActionType::Forward);
        }
        group.PushAction(ActionType::TurnLeft);
        group.PushAction(ActionType::Forward);
        group.PushAction(ActionType::TurnLeft);
        return group;
    }
};
}  // namespace adas
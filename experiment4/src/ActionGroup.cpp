#include "ActionGroup.hpp"

namespace adas
{
ActionGroup::ActionGroup(std::initializer_list<ActionType> initialActions) noexcept : actions(initialActions)
{
}

void ActionGroup::PushAction(ActionType action) noexcept
{
    actions.push_back(action);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    for (const auto action : actions) {
        switch (action) {
        case ActionType::Forward:
            poseHandler.Forward();
            break;
        case ActionType::Backward:
            poseHandler.Backward();
            break;
        case ActionType::TurnLeft:
            poseHandler.TurnLeft();
            break;
        case ActionType::TurnRight:
            poseHandler.TurnRight();
            break;
        case ActionType::ToggleFast:
            poseHandler.Fast();
            break;
        case ActionType::ToggleReverse:
            poseHandler.Reverse();
            break;
        }
    }
}
}

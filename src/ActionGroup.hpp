#pragma once

#include <initializer_list>
#include <vector>

#include "PoseHandler.hpp"

namespace adas
{
enum class ActionType
{
    Forward,
    Backward,
    TurnLeft,
    TurnRight,
    ToggleFast,
    ToggleReverse,
};

class ActionGroup final
{
public:
    ActionGroup() = default;
    explicit ActionGroup(std::initializer_list<ActionType> initialActions) noexcept;

    void PushAction(ActionType action) noexcept;
    void DoOperate(PoseHandler& poseHandler) const noexcept;

private:
    std::vector<ActionType> actions;
};
}

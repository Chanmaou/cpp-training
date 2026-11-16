#pragma once

#include "Executor.hpp"

namespace adas
{
class PoseHandler final
{
public:
    explicit PoseHandler(const Pose& pose) noexcept;

    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Move() noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
    void Reverse() noexcept;
    bool IsReverse() const noexcept;
    Pose Query() const noexcept;

private:
    void MoveOneStep(int step) noexcept;

    Pose pose;
    bool fast{false};
    bool reverse{false};
};
}  // namespace adas
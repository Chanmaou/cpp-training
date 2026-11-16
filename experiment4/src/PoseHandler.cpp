#include "PoseHandler.hpp"

namespace adas
{
PoseHandler::PoseHandler(const Pose& initialPose) noexcept : pose(initialPose)
{
}

void PoseHandler::Move() noexcept
{
    MoveOneStep(reverse ? -1 : 1);
}

void PoseHandler::Forward() noexcept
{
    MoveOneStep(1);
}

void PoseHandler::Backward() noexcept
{
    MoveOneStep(-1);
}

void PoseHandler::MoveOneStep(int step) noexcept
{
    if (pose.heading == 'E') {
        pose.x += step;
    } else if (pose.heading == 'W') {
        pose.x -= step;
    } else if (pose.heading == 'N') {
        pose.y += step;
    } else if (pose.heading == 'S') {
        pose.y -= step;
    }
}

void PoseHandler::TurnLeft() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}

void PoseHandler::TurnRight() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}
}  // namespace adas
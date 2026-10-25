#include "ExecutorImpl.hpp"

#include <memory>
#include <new>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : pose(initialPose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto command : commands) {
        if (command == 'F') {
            fast = !fast;
        } else if (command == 'M') {
            std::unique_ptr<MoveCommand> commandObject = std::make_unique<MoveCommand>();
            commandObject->DoOperate(*this);
        } else if (command == 'L') {
            std::unique_ptr<TurnLeftCommand> commandObject = std::make_unique<TurnLeftCommand>();
            commandObject->DoOperate(*this);
        } else if (command == 'R') {
            if (fast) {
                Move();
            }
            TurnRight();
        }
    }
}

void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 'E') {
        ++pose.x;
    } else if (pose.heading == 'W') {
        --pose.x;
    } else if (pose.heading == 'N') {
        ++pose.y;
    } else if (pose.heading == 'S') {
        --pose.y;
    }
}

void ExecutorImpl::TurnLeft() noexcept
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

void ExecutorImpl::TurnRight() noexcept
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

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

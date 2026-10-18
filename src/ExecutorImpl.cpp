#include "ExecutorImpl.hpp"

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
        if (command == 'M') {
            if (pose.heading == 'E') {
                ++pose.x;
            } else if (pose.heading == 'W') {
                --pose.x;
            } else if (pose.heading == 'N') {
                ++pose.y;
            } else if (pose.heading == 'S') {
                --pose.y;
            }
        } else if (command == 'L') {
            if (pose.heading == 'E') {
                pose.heading = 'N';
            } else if (pose.heading == 'N') {
                pose.heading = 'W';
            } else if (pose.heading == 'W') {
                pose.heading = 'S';
            } else if (pose.heading == 'S') {
                pose.heading = 'E';
            }
        } else if (command == 'R') {
            if (pose.heading == 'E') {
                pose.heading = 'S';
            } else if (pose.heading == 'S') {
                pose.heading = 'W';
            } else if (pose.heading == 'W') {
                pose.heading = 'N';
            }
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

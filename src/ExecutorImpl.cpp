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
            }
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

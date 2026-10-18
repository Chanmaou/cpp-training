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

void ExecutorImpl::Execute(const std::string&) noexcept
{
    // 用例 1 尚未涉及移动和转向指令
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

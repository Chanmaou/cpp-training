#include "ExecutorImpl.hpp"

#include <new>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose&) noexcept : pose{0, 0, 'S'}
{
    // 临时错误实现：尚未保存传入的初始位置，用于验证两个测试都能发现问题。
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

#include "ExecutorImpl.hpp"

#include <functional>
#include <new>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : poseHandler(initialPose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const std::unordered_map<char, std::function<void(PoseHandler&)>> commandMap{
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
    };

    for (const auto command : commands) {
        const auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
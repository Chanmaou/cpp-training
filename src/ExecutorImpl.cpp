#include "ExecutorImpl.hpp"

#include <memory>
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
    std::unordered_map<char, std::unique_ptr<ICommand>> commandMap;
    commandMap.emplace('M', std::make_unique<MoveCommand>());
    commandMap.emplace('L', std::make_unique<TurnLeftCommand>());
    commandMap.emplace('R', std::make_unique<TurnRightCommand>());
    commandMap.emplace('F', std::make_unique<FastCommand>());

    for (const auto command : commands) {
        const auto it = commandMap.find(command);
        if (it != commandMap.end()) {
            it->second->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
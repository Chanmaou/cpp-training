#include "ExecutorImpl.hpp"

#include <memory>
#include <new>

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
    for (const auto command : commands) {
        std::unique_ptr<ICommand> commandObject;

        if (command == 'F') {
            commandObject = std::make_unique<FastCommand>();
        } else if (command == 'M') {
            commandObject = std::make_unique<MoveCommand>();
        } else if (command == 'L') {
            commandObject = std::make_unique<TurnLeftCommand>();
        } else if (command == 'R') {
            commandObject = std::make_unique<TurnRightCommand>();
        }

        if (commandObject) {
            commandObject->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas

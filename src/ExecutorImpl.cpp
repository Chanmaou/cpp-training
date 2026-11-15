#include "ExecutorImpl.hpp"

#include <new>

#include "CmderFactory.hpp"
#include "Singleton.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose, VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose, VehicleType type) noexcept
    : poseHandler(initialPose), vehicleType(type)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const auto cmders = Singleton<CmderFactory>::Instance().GetCmders(commands, vehicleType);
    for (const auto& cmder : cmders) {
        cmder(poseHandler).DoOperate(poseHandler);
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
}  // namespace adas
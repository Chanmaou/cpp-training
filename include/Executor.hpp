#pragma once

#include <string>

namespace adas
{
struct Pose {
    int x;
    int y;
    char heading;
};

enum class VehicleType {
    Normal,
    SportsCar,
};

class Executor
{
public:
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}, VehicleType type = VehicleType::Normal) noexcept;
    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& command) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};
}  // namespace adas

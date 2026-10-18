#pragma once

#include <string>

namespace adas
{
struct Pose {
    int x;
    int y;
    char heading;
};

class Executor
{
public:
    // 使用完后由调用者负责删除返回的对象
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}) noexcept;

    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& command) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};
}  // namespace adas

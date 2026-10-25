#pragma once

#include "Executor.hpp"

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept override = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

    void Execute(const std::string& command) noexcept override;
    Pose Query() const noexcept override;

private:
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;

private:
    class MoveCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            if (executor.fast) {
                executor.Move();
            }
            executor.Move();
        }
    };

private:
    Pose pose;
    bool fast{false};
};
}  // namespace adas

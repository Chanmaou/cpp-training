#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
TEST(ExecutorFastTest, should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E)
{
    // 初始位置为原点，朝东
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // 开启加速，再向前移动
    executor->Execute("FM");

    // 加速时应向东前进两格
    const Pose expected{2, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E)
{
    // 初始位置为原点，朝东
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // 开启加速，再执行左转指令
    executor->Execute("FL");

    // 加速左转应先向东前进一步，再转向北
    const Pose expected{1, 0, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E)
{
    // 初始位置为原点，朝东
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // 开启加速，再执行右转指令
    executor->Execute("FR");

    // 加速右转应先向东前进一步，再转向南
    const Pose expected{1, 0, 'S'};
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace adas

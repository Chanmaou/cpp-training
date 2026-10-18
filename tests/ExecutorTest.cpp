#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas
{
bool operator==(const Pose& lhs, const Pose& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}

TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // 创建一辆初始位置为 (0, 0)、朝向东 E 的车
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // 没有执行任何移动或转向指令，查询结果应保持初始状态
    const Pose expected{0, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // 不指定初始位置，也不执行任何指令
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // 默认位置应为 (0, 0)，朝向北 N
    const Pose expected{0, 0, 'N'};
    ASSERT_EQ(expected, executor->Query());
}
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
{
    // 初始位置为 (0, 0)，朝向东 E
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    executor->Execute("M");

    // 向东前进一步，横坐标增加 1，朝向保持不变
    const Pose expected{1, 0, 'E'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
{
    // 初始位置为 (0, 0)，朝向西 W
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    executor->Execute("M");

    // 向西前进一步，横坐标减少 1，朝向保持不变
    const Pose expected{-1, 0, 'W'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N)
{
    // 初始位置为 (0, 0)，朝向北 N
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    executor->Execute("M");

    // 向北前进一步，纵坐标增加 1，朝向保持不变
    const Pose expected{0, 1, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S)
{
    // 初始位置为 (0, 0)，朝向南 S
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'S'}));

    executor->Execute("M");

    // 向南前进一步，纵坐标减少 1，朝向保持不变
    const Pose expected{0, -1, 'S'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E)
{
    // 初始位置为 (0, 0)，朝向东 E
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    executor->Execute("L");

    // 向左转后朝向北 N，位置不变
    const Pose expected{0, 0, 'N'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N)
{
    // 初始位置为 (0, 0)，朝向北 N
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));

    executor->Execute("L");

    // 向左转后朝向西 W，位置不变
    const Pose expected{0, 0, 'W'};
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W)
{
    // 初始位置为 (0, 0)，朝向西 W
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    executor->Execute("L");

    // 向左转后朝向南 S，位置不变
    const Pose expected{0, 0, 'S'};
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace adas

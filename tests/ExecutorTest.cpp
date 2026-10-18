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
}  // namespace adas

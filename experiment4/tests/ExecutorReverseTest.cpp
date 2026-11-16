#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
namespace
{
void CheckReverse(const Pose& initial, const std::string& commands, const Pose& expected)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor(initial));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace

TEST(ExecutorReverseTest, BM_facing_E)
{
    CheckReverse({0, 0, 'E'}, "BM", {-1, 0, 'E'});
}

TEST(ExecutorReverseTest, BM_facing_W)
{
    CheckReverse({0, 0, 'W'}, "BM", {1, 0, 'W'});
}

TEST(ExecutorReverseTest, BM_facing_N)
{
    CheckReverse({0, 0, 'N'}, "BM", {0, -1, 'N'});
}

TEST(ExecutorReverseTest, BM_facing_S)
{
    CheckReverse({0, 0, 'S'}, "BM", {0, 1, 'S'});
}

TEST(ExecutorReverseTest, BL_turns_right_without_moving)
{
    CheckReverse({0, 0, 'E'}, "BL", {0, 0, 'S'});
}

TEST(ExecutorReverseTest, BR_turns_left_without_moving)
{
    CheckReverse({0, 0, 'E'}, "BR", {0, 0, 'N'});
}

TEST(ExecutorReverseTest, BFM_moves_backward_two_steps)
{
    CheckReverse({0, 0, 'E'}, "BFM", {-2, 0, 'E'});
}

TEST(ExecutorReverseTest, BFL_moves_backward_then_turns_right)
{
    CheckReverse({0, 0, 'E'}, "BFL", {-1, 0, 'S'});
}

TEST(ExecutorReverseTest, BFR_moves_backward_then_turns_left)
{
    CheckReverse({0, 0, 'E'}, "BFR", {-1, 0, 'N'});
}

TEST(ExecutorReverseTest, BBM_cancels_reverse)
{
    CheckReverse({0, 0, 'N'}, "BBM", {0, 1, 'N'});
}

TEST(ExecutorReverseTest, cancel_reverse_keeps_fast)
{
    CheckReverse({0, 0, 'E'}, "BFBM", {2, 0, 'E'});
}

TEST(ExecutorReverseTest, cancel_fast_keeps_reverse)
{
    CheckReverse({0, 0, 'E'}, "BFFM", {-1, 0, 'E'});
}

TEST(ExecutorReverseTest, FBM_also_moves_backward_two_steps)
{
    CheckReverse({0, 0, 'E'}, "FBM", {-2, 0, 'E'});
}

TEST(ExecutorReverseTest, reverse_persists_between_execute_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("B");
    executor->Execute("M");

    const Pose afterMove{-1, 0, 'E'};
    ASSERT_EQ(afterMove, executor->Query());

    executor->Execute("L");

    const Pose afterTurn{-1, 0, 'S'};
    ASSERT_EQ(afterTurn, executor->Query());
}
}  // namespace adas
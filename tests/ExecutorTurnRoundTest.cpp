#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
namespace
{
void CheckTurnRound(const std::string& commands, const Pose& expected)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}
}  // namespace

TEST(ExecutorTurnRoundTest, normal)
{
    CheckTurnRound("TR", {0, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, fast)
{
    CheckTurnRound("FTR", {1, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, reverse_ignored)
{
    CheckTurnRound("BTR", {0, 0, 'E'});
}

TEST(ExecutorTurnRoundTest, fast_reverse_ignored)
{
    CheckTurnRound("BFTR", {0, 0, 'E'});
}

TEST(ExecutorTurnRoundTest, twice)
{
    CheckTurnRound("TRTR", {0, 0, 'E'});
}

TEST(ExecutorTurnRoundTest, move_after_turn_round)
{
    CheckTurnRound("TRM", {-1, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, reverse_state_kept)
{
    CheckTurnRound("BTRM", {-1, 0, 'E'});
}

TEST(ExecutorTurnRoundTest, fast_state_kept)
{
    CheckTurnRound("FTRM", {-1, 1, 'W'});
}
}  // namespace adas
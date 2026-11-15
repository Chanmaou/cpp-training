#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
struct SportsCarCase {
    const char* name;
    Pose initial;
    const char* commands;
    Pose expected;
};

class SportsCarTest : public ::testing::TestWithParam<SportsCarCase>
{
};

TEST_P(SportsCarTest, ExecutesCommands)
{
    const auto& data = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor(data.initial, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute(data.commands);
    ASSERT_EQ(data.expected, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(SportsCarCases, SportsCarTest,
                         ::testing::Values(SportsCarCase{"NormalM", {0, 0, 'E'}, "M", {2, 0, 'E'}},
                                           SportsCarCase{"NormalL", {0, 0, 'E'}, "L", {0, 1, 'N'}},
                                           SportsCarCase{"NormalR", {0, 0, 'E'}, "R", {0, -1, 'S'}},
                                           SportsCarCase{"ReverseM", {0, 0, 'E'}, "BM", {-2, 0, 'E'}},
                                           SportsCarCase{"ReverseL", {0, 0, 'E'}, "BL", {0, 1, 'S'}},
                                           SportsCarCase{"ReverseR", {0, 0, 'E'}, "BR", {0, -1, 'N'}},
                                           SportsCarCase{"FastM", {0, 0, 'E'}, "FM", {4, 0, 'E'}},
                                           SportsCarCase{"FastL", {0, 0, 'E'}, "FL", {1, 1, 'N'}},
                                           SportsCarCase{"FastR", {0, 0, 'E'}, "FR", {1, -1, 'S'}},
                                           SportsCarCase{"FastReverseM", {0, 0, 'E'}, "BFM", {-4, 0, 'E'}},
                                           SportsCarCase{"FastReverseL", {0, 0, 'E'}, "BFL", {-1, 1, 'S'}},
                                           SportsCarCase{"FastReverseR", {0, 0, 'E'}, "BFR", {-1, -1, 'N'}},
                                           SportsCarCase{"FacingNorth", {0, 0, 'N'}, "M", {0, 2, 'N'}},
                                           SportsCarCase{"FacingWest", {0, 0, 'W'}, "M", {-2, 0, 'W'}},
                                           SportsCarCase{"FacingSouth", {0, 0, 'S'}, "M", {0, -2, 'S'}},
                                           SportsCarCase{"NonOriginSequence", {2, 3, 'E'}, "MLM", {4, 6, 'N'}},
                                           SportsCarCase{"CancelFast", {0, 0, 'E'}, "FFM", {2, 0, 'E'}},
                                           SportsCarCase{"CancelReverse", {0, 0, 'E'}, "BBM", {2, 0, 'E'}}),
                         [](const ::testing::TestParamInfo<SportsCarCase>& info) {
                             return std::string(info.param.name);
                         });

TEST(SportsCarStateTest, StatePersistsAcrossCalls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("F");
    executor->Execute("B");
    executor->Execute("M");
    const Pose fastReverse{-4, 0, 'E'};
    ASSERT_EQ(fastReverse, executor->Query());

    executor->Execute("F");
    executor->Execute("M");
    const Pose reverseOnly{-6, 0, 'E'};
    ASSERT_EQ(reverseOnly, executor->Query());

    executor->Execute("B");
    executor->Execute("M");
    const Pose normal{-4, 0, 'E'};
    ASSERT_EQ(normal, executor->Query());
}

TEST(SportsCarStateTest, ExecutorsHaveIndependentStates)
{
    std::unique_ptr<Executor> sportsA(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    std::unique_ptr<Executor> sportsB(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    std::unique_ptr<Executor> normal(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, sportsA.get());
    ASSERT_NE(nullptr, sportsB.get());
    ASSERT_NE(nullptr, normal.get());

    sportsA->Execute("BFM");
    sportsB->Execute("M");
    normal->Execute("M");

    const Pose expectedA{-4, 0, 'E'};
    const Pose expectedB{2, 0, 'E'};
    const Pose expectedNormal{1, 0, 'E'};
    ASSERT_EQ(expectedA, sportsA->Query());
    ASSERT_EQ(expectedB, sportsB->Query());
    ASSERT_EQ(expectedNormal, normal->Query());
}
}  // namespace adas
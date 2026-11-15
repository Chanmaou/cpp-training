#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{
struct BusCase {
    const char* name;
    Pose initial;
    const char* commands;
    Pose expected;
};

class BusTest : public ::testing::TestWithParam<BusCase>
{
};

TEST_P(BusTest, ExecutesCommands)
{
    const auto& data = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor(data.initial, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute(data.commands);
    ASSERT_EQ(data.expected, executor->Query());
}

INSTANTIATE_TEST_SUITE_P(
    BusCases, BusTest,
    ::testing::Values(
        BusCase{"NormalM", {0, 0, 'E'}, "M", {1, 0, 'E'}}, BusCase{"NormalL", {0, 0, 'E'}, "L", {1, 0, 'N'}},
        BusCase{"NormalR", {0, 0, 'E'}, "R", {1, 0, 'S'}}, BusCase{"ReverseM", {0, 0, 'E'}, "BM", {-1, 0, 'E'}},
        BusCase{"ReverseL", {0, 0, 'E'}, "BL", {-1, 0, 'S'}}, BusCase{"ReverseR", {0, 0, 'E'}, "BR", {-1, 0, 'N'}},
        BusCase{"FastM", {0, 0, 'E'}, "FM", {2, 0, 'E'}}, BusCase{"FastL", {0, 0, 'E'}, "FL", {2, 0, 'N'}},
        BusCase{"FastR", {0, 0, 'E'}, "FR", {2, 0, 'S'}}, BusCase{"FastReverseM", {0, 0, 'E'}, "BFM", {-2, 0, 'E'}},
        BusCase{"FastReverseL", {0, 0, 'E'}, "BFL", {-2, 0, 'S'}},
        BusCase{"FastReverseR", {0, 0, 'E'}, "BFR", {-2, 0, 'N'}},
        BusCase{"FacingNorth", {0, 0, 'N'}, "M", {0, 1, 'N'}}, BusCase{"FacingWest", {0, 0, 'W'}, "M", {-1, 0, 'W'}},
        BusCase{"FacingSouth", {0, 0, 'S'}, "M", {0, -1, 'S'}},
        BusCase{"NonOriginSequence", {2, 3, 'E'}, "MLM", {4, 4, 'N'}},
        BusCase{"CancelFast", {0, 0, 'E'}, "FFM", {1, 0, 'E'}},
        BusCase{"CancelReverse", {0, 0, 'E'}, "BBM", {1, 0, 'E'}}),
    [](const ::testing::TestParamInfo<BusCase>& info) { return std::string(info.param.name); });

TEST(BusStateTest, StatePersistsAcrossCalls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    ASSERT_NE(nullptr, executor.get());

    executor->Execute("F");
    executor->Execute("B");
    executor->Execute("L");
    const Pose fastReverse{-2, 0, 'S'};
    ASSERT_EQ(fastReverse, executor->Query());

    executor->Execute("F");
    executor->Execute("M");
    const Pose reverseOnly{-2, 1, 'S'};
    ASSERT_EQ(reverseOnly, executor->Query());

    executor->Execute("B");
    executor->Execute("R");
    const Pose normal{-2, 0, 'W'};
    ASSERT_EQ(normal, executor->Query());
}

TEST(BusStateTest, ExecutorsHaveIndependentStates)
{
    std::unique_ptr<Executor> busA(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    std::unique_ptr<Executor> busB(Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    std::unique_ptr<Executor> sports(Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    ASSERT_NE(nullptr, busA.get());
    ASSERT_NE(nullptr, busB.get());
    ASSERT_NE(nullptr, sports.get());

    busA->Execute("BFL");
    busB->Execute("L");
    sports->Execute("L");

    const Pose expectedA{-2, 0, 'S'};
    const Pose expectedB{1, 0, 'N'};
    const Pose expectedSports{0, 1, 'N'};
    ASSERT_EQ(expectedA, busA->Query());
    ASSERT_EQ(expectedB, busB->Query());
    ASSERT_EQ(expectedSports, sports->Query());
}
}  // namespace adas
#include "ExecutorImpl.hpp"

#include <new>

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : pose(initialPose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto command : commands) {
        if (command == 'F') {
            fast = !fast;
        } else if (command == 'M') {
            const int steps = fast ? 2 : 1;
            for (int step = 0; step < steps; ++step) {
                if (pose.heading == 'E') {
                    ++pose.x;
                } else if (pose.heading == 'W') {
                    --pose.x;
                } else if (pose.heading == 'N') {
                    ++pose.y;
                } else if (pose.heading == 'S') {
                    --pose.y;
                }
            }
        } else if (command == 'L') {
            if (fast) {
                if (pose.heading == 'E') {
                    ++pose.x;
                } else if (pose.heading == 'W') {
                    --pose.x;
                } else if (pose.heading == 'N') {
                    ++pose.y;
                } else if (pose.heading == 'S') {
                    --pose.y;
                }
            }
            if (pose.heading == 'E') {
                pose.heading = 'N';
            } else if (pose.heading == 'N') {
                pose.heading = 'W';
            } else if (pose.heading == 'W') {
                pose.heading = 'S';
            } else if (pose.heading == 'S') {
                pose.heading = 'E';
            }
        } else if (command == 'R') {
            if (fast) {
                if (pose.heading == 'E') {
                    ++pose.x;
                } else if (pose.heading == 'W') {
                    --pose.x;
                } else if (pose.heading == 'N') {
                    ++pose.y;
                } else if (pose.heading == 'S') {
                    --pose.y;
                }
            }
            if (pose.heading == 'E') {
                pose.heading = 'S';
            } else if (pose.heading == 'S') {
                pose.heading = 'W';
            } else if (pose.heading == 'W') {
                pose.heading = 'N';
            } else if (pose.heading == 'N') {
                pose.heading = 'E';
            }
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas

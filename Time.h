#pragma once
#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace arkanoid {

    std::chrono::time_point<std::chrono::high_resolution_clock>
        getCurrentTime();

    double getElapsedTime(
        const std::chrono::time_point<
        std::chrono::high_resolution_clock>& first,
        const std::chrono::time_point<
        std::chrono::high_resolution_clock>& last);

    void wait(const std::chrono::milliseconds& milliseconds);
}  // namespace arkanoid
#endif
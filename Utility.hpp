#pragma once
#include <chrono>

template <class Type, class Ratio>
struct ScopedTimer
{
public:
    using duration_t = std::chrono::duration<Type, Ratio>;
public:
    ScopedTimer(duration_t& out_duration) : out_duration(out_duration)
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~ScopedTimer()
    {
        out_duration = std::chrono::duration_cast<duration_t>(std::chrono::high_resolution_clock::now() - start);
    }

private:
    std::chrono::high_resolution_clock::time_point start;
    duration_t& out_duration;
};
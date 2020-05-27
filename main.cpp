#include "Sorts/BucketSort.hpp"
#include "Utility.hpp"

#include <algorithm>
#include <vector>
#include <random>
#include <cassert>
#include <iostream>

void nbubble_sort(std::vector<int>& vec)
{
    const std::int64_t n = vec.size();
    for (std::int64_t i = 0; i < n; i++)
    {
        const int start = i % 2;

    #pragma omp parallel for
        for (std::int64_t j = start; j < n - 1; j += 2)
        {
            if (vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main([[maybe_unused]] int argc, char** argv)
{

    std::random_device r;

    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(INT_MIN, INT_MAX);

    std::vector<int> vec(100000);

    std::chrono::duration<double> sort_duration;

    {
        std::generate(vec.begin(), vec.end(), [&]() { return uniform_dist(e); });
        ScopedTimer _(sort_duration);
        bucket_sort_seq(vec);
    }
    assert(std::is_sorted(vec.begin(), vec.end()));
    std::cout << "Sequenced sorting: " << sort_duration.count() << " s\n";
    std::shuffle(vec.begin(), vec.end(), e);
    {
        ScopedTimer _(sort_duration);
        bucket_sort_omp(vec);
    }
    assert(std::is_sorted(vec.begin(), vec.end()));
    std::cout << "OpenMP sorting: " << sort_duration.count() << " s\n";

    return 0;
}
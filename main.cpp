#include "Sorts/BucketSort_OMP.hpp"
#include "Sorts/BucketSort_SEQ.hpp"
#include "Utility.hpp"

#include <algorithm>
#include <vector>
#include <random>
#include <cassert>
#include <iostream>

int main([[maybe_unused]] int argc, char** argv)
{
    std::random_device r;

    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(INT_MIN, INT_MAX);

    std::vector<int> vec(50000000);

    std::chrono::duration<double> sort_duration;

    {
        std::generate(vec.begin(), vec.end(), [&]() { return uniform_dist(e); });
        ScopedTimer _(sort_duration);
        bucket_sort_seq(vec.begin(), vec.end());
    }
    assert(std::is_sorted(vec.begin(), vec.end()));
    std::cout << "Sequenced sorting: " << sort_duration.count() << " s\n";
    std::shuffle(vec.begin(), vec.end(), e);
    {
        ScopedTimer _(sort_duration);
        bucket_sort_omp(vec.begin(), vec.end());
    }
    assert(std::is_sorted(vec.begin(), vec.end()));
    std::cout << "OpenMP sorting: " << sort_duration.count() << " s\n";

    return 0;
}
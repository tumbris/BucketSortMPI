#include "BucketSort.hpp"

#include <algorithm>
#include <array>
#include <vector>

void oddeven_sort_seq(std::vector<int>& vec)
{
    const std::int64_t n = vec.size();
    for (std::int64_t i = 0; i < n; i++)
    {
        const auto start = i % 2;
        for (std::int64_t j = start; j < n - 1; j += 2)
        {
            if (vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void bucket_sort_seq(std::vector<int>& vec)
{
    static constexpr std::size_t INTEGER_BASE = 10;

    const auto [min_element, max_element] = std::minmax_element(vec.begin(), vec.end());
    static const std::int64_t interval = std::max<std::int64_t>((*max_element - *min_element) / INTEGER_BASE, 1);
    std::vector<std::vector<int>> buckets(INTEGER_BASE * 2 + 1);

    for (auto i : vec)
    {
        std::int64_t temp_index = i / interval;
        std::size_t index = temp_index + INTEGER_BASE;
        buckets[index].push_back(i);
    }

    for (auto& bucket : buckets)
    {
        oddeven_sort_seq(bucket);
    }

    std::size_t count = 0;
    for (const auto& bucket : buckets)
    {
        for (auto e : bucket)
        {
            vec[count++] = e;
        }
    }
}
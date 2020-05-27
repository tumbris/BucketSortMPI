#include <algorithm>
#include <array>
#include <limits>
#include <vector>
#include <thread>
#include <omp.h>
#include <future>
#include <execution>

template <class RandomAccessIt>
void bucket_sort_omp(RandomAccessIt first, RandomAccessIt last)
{
    static constexpr std::size_t INTEGER_BASE = 10;

    using value_type = std::remove_reference_t<decltype(*first)>;
    using bucket_t = std::vector<value_type>;

    static_assert(std::is_integral_v<value_type>, "This realization of bucket_sort supports only integer types!");

    const auto [min_element, max_element] = std::minmax_element(first, last);

    static const std::int64_t interval = std::max<std::int64_t>((*max_element - *min_element) / INTEGER_BASE, 1);

    std::vector<bucket_t> buckets(INTEGER_BASE * 2 + 1 /*for negative numbers too*/);

    std::int64_t size = last - first;

    for (auto head = first; head != last; ++head)
    {
        value_type temp = *head;
        std::int64_t temp_index = temp / interval;
        std::size_t index = temp_index + INTEGER_BASE;
        buckets[index].push_back(*head);
    }

#pragma omp parallel for
    for (std::int64_t i = 0; i < buckets.size(); ++i)
    {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    //std::vector<std::future<void>> f;
    //for (auto& bucket : buckets)
    //{
    //    f.emplace_back(std::async(std::launch::async,
    //                   [&]()
    //                   {
    //                       std::sort(bucket.begin(), bucket.end());
    //                   }));
    //}

    //for (auto& fut : f) fut.wait();

    for (const auto& bucket : buckets)
    {
        for (auto e : bucket)
        {
            *(first++) = e;
        }
    }
}
#include <algorithm>
#include <array>
#include <limits>
#include <vector>
#include <execution>

template <class RandomAccessIt>
void bucket_sort_seq(RandomAccessIt first, RandomAccessIt last)
{
    using value_type = std::remove_reference_t<decltype(*first)>;
    using bucket_t = std::vector<value_type>;

    static_assert(std::is_integral_v<value_type>, "This realization of bucket_sort supports only integer types!");
    static constexpr std::size_t INTEGER_BASE = 10;

    const auto [min_element, max_element] = std::minmax_element(first, last);
    
    static const std::int64_t interval = std::max<std::int64_t>((*max_element - *min_element) / INTEGER_BASE, 1);

    std::array<bucket_t, INTEGER_BASE * 2 + 1 /*for negative numbers too*/> buckets;

    for (auto head = first; head != last; ++head)
    {
        value_type temp = *head;
        std::int64_t temp_index = temp / interval;
        std::size_t index = temp_index + INTEGER_BASE;
        buckets[index].push_back(*head);
    }

    for (auto& bucket : buckets)
    {
        std::sort(bucket.begin(), bucket.end());
    }

    for (const auto& bucket : buckets)
    {
        for (auto e : bucket)
        {
            *(first++) = e;
        }
    }
}
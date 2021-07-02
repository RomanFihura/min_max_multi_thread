#include "min_max_multi_thread.h"

std::random_device rd;
std::mt19937 gen1(rd());

void vector_insert(std::vector<uint32_t> &v, uint32_t max, uint32_t amount)
{
    for (uint32_t i = 0; i < amount; i++)
    {
        v.push_back((gen1() % max) + 1);
    }
};
void min_max(uint32_tCIt begin, uint32_tCIt end, std::pair<uint32_tCIt, uint32_tCIt> &minMax)
{

    minMax = std::minmax_element(begin, end);
}

std::pair<uint32_tCIt, uint32_tCIt> multi_thr(const std::vector<uint32_t> &v)
{
    if (v.empty())
    {
        throw std::invalid_argument("Input vector is empty");
    }
    uint32_t coreCount = std::max(std::thread::hardware_concurrency(), 1u);
    const auto step = v.size() / coreCount;

    std::vector<std::thread> threads;
    std::vector<std::pair<uint32_tCIt, uint32_tCIt>> threadsMinMax;
    threadsMinMax.reserve(coreCount);

    auto curBeg = v.begin();
    auto curEnd = (v.begin() + step) > v.end() ? v.end() : (v.begin() + step);
    for (uint32_t i = 0; i < coreCount; i++)
    {
        std::pair<uint32_tCIt, uint32_tCIt> t{{}, {}};
        threadsMinMax.push_back(std::pair<uint32_tCIt, uint32_tCIt>{{}, {}});
        threads.emplace_back(min_max, curBeg, curEnd, std::ref(threadsMinMax.back()));

        curBeg = curEnd;
        curEnd = (v.end() - step) < curBeg ? v.end() : (curBeg + step);
    }

    for (auto &entry : threads)
    {
        entry.join();
    }

    uint32_tCIt min = threadsMinMax.back().first;
    uint32_tCIt max = threadsMinMax.back().second;

    for (const auto &el : threadsMinMax)
    {
        min = (*el.first < *min) ? el.first : min;
        max = (*el.second > *max) ? el.second : max;
    }

    return {min, max};
};
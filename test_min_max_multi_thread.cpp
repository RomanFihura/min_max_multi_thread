#include "min_max_multi_thread.h"

#include <gtest/gtest.h>
TEST(Test, min_correct)
{
    std::vector<uint32_t> test;
    vector_insert(test, 100000, 5000);
    const auto minMax = multi_thr(test);
    auto min = *std::min_element(std::begin(test), std::end(test));
    EXPECT_EQ(*minMax.first, min);
}
TEST(Test, max_correct)
{
    std::vector<uint32_t> test;
    vector_insert(test, 100000, 5000);
    const auto minMax = multi_thr(test);
    auto max = *std::max_element(std::begin(test), std::end(test));
    EXPECT_EQ(*minMax.second, max);
}

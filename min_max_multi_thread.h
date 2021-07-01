#pragma once

#include <algorithm>
#include <random>
#include <thread>
#include <vector>

using uint32_tCIt = std::vector<uint32_t>::const_iterator;
void vector_insert(std::vector<uint32_t> &v, uint32_t max, uint32_t amount);
std::pair<uint32_tCIt, uint32_tCIt> multi_thr(const std::vector<uint32_t> &v);

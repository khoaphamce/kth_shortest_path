#pragma once

#include <algorithm>
#include "math_algo.h"
#include <vector>
#include <iostream>

#ifndef algo_h
#define algo_h

namespace algo
{
// CREATE ALL PERMUTATION OF EDGES' ORDER
std::vector<std::vector<std::vector<long int>>> edges_order_perm(std::vector<std::vector<long int>> edgesVec);
}
#endif
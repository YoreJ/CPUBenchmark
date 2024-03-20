#pragma once
#include "PerfCounter.h"
#include <vector>
#include <random>
#include <thread>
#include <algorithm>

namespace Matrix
{
    std::vector<std::vector<ll>> MatrixPrepare(int Row, int Col) ;
    std::vector<std::vector<ll>> MatrixMultiply(std::vector<std::vector<ll>>& A, std::vector<std::vector<ll>>& B);
    Tuple MultiplyTest(int TestSize, PerfCounter& pc);
}
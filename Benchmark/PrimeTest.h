#pragma once
#include <bits/stdc++.h>
#include "PerfCounter.h"

namespace Prime
{
    extern bool IsPrime(int n, std::vector<long long>& PrimeList);
    extern Tuple PrimeTest(int n, PerfCounter& pc);
}
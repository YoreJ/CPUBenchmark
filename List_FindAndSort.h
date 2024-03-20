#pragma once
#include "PerfCounter.h"
#include <list>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>

namespace List_FindAndSort
{
    std::list<int> ListPrepare(int Size);
    std::list<int> Merge(std::list<int>& left, std::list<int>& right);
    std::list<int> mergeSort(std::list<int>& lst, int depth);
    Tuple FindTest(int TestSize, PerfCounter& pc);
    Tuple SortTest(int TestSize, PerfCounter& pc);
}
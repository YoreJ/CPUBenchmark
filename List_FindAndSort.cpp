#include "List_FindAndSort.h"
using namespace std;

list<int> List_FindAndSort::ListPrepare(int Size) 
{
    list<int> lst;
    vector<int> v(Size);
    for (int i = 0; i < Size; ++i) v[i] = i;
    shuffle(v.begin(), v.end(), default_random_engine(0));
    for (int i = 0; i < Size; ++i) lst.push_back(v[i]);
    return lst;
}

list<int> List_FindAndSort::Merge(list<int>& left, list<int>& right) 
{
    list<int> Result;
    auto ItLeft = left.begin();
    auto ItRight = right.begin();
    while (ItLeft != left.end() && ItRight != right.end()) 
    {
        if (*ItLeft < *ItRight) Result.push_back(*ItLeft++);
        else Result.push_back(*ItRight++);
    }
    Result.splice(Result.end(), left, ItLeft, left.end());
    Result.splice(Result.end(), right, ItRight, right.end());
    return Result;
}

list<int> List_FindAndSort::mergeSort(list<int>& lst, int depth = 0) 
{
    if (lst.size() <= 1) return lst;
    auto mid = next(lst.begin(), lst.size() / 2);
    list<int> left(lst.begin(), mid);
    list<int> right(mid, lst.end());
    list<int> SortedLeft, SortedRight;
    if (depth < 3) 
    {
        thread t1([&] { SortedLeft = mergeSort(left, depth + 1); });
        thread t2([&] { SortedRight = mergeSort(right, depth + 1); });
        t1.join();
        t2.join();
    } 
    else 
    {
        SortedLeft = mergeSort(left, depth + 1);
        SortedRight = mergeSort(right, depth + 1);
    }

    return Merge(SortedLeft, SortedRight);
}

Tuple List_FindAndSort::FindTest(int TestSize, PerfCounter& pc) 
{
    pc.reset();
    list<int> lst = ListPrepare(TestSize);
    list<int>::iterator it;
    pc.start();
    for (int i = 0; i < TestSize; ++i)
    {
        it = lst.begin();
        while(it != lst.end() && *it != i) ++it;
    }
    return pc.stop();
}

Tuple List_FindAndSort::SortTest(int TestSize, PerfCounter& pc) 
{
    pc.reset();
    list<int> lst = ListPrepare(TestSize);
    pc.start();
    list<int> SortedLst = mergeSort(lst);
    return pc.stop();
}
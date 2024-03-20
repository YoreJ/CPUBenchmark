#pragma once
#include <string>
#include "pugixml.hpp"

struct ParamType1
{
    int Size;
    int Iter;
};

struct ParamType2
{
    std::string Path;
    int Iter;
};

struct ParamType3
{
    std::string PathA, PathB;
    int Qua, Thrd, Iteration, Iter;
};
#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "pugixml.hpp"
#include "PerfCounter.h"

extern void PrintNode(const pugi::xml_node &Node, std::ofstream &output, int Depth);
extern Tuple XMLAnal(std::string Path, PerfCounter& pc);
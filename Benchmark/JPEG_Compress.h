#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <atomic>
#include "PerfCounter.h"

#include "stb_image_write.h"
#include "stb_image.h"

extern std::mutex mutex;
extern std::atomic<int> compressionCounter;

namespace JPEG_Compress 
{
    struct RGBColor {
        uint8_t r, g, b;
    };

    extern void performIntensiveCalculation();

    extern void compressJPEGThread(const char* inputFileName, const char* outputFileName, int quality, int iterations);

    extern int compressJPEG(const char* inputFileName, const char* outputFileName, int quality, int numThreads, int iterations);

    extern Tuple JPEGCompTest(std::string Input, std::string Output, int Quality, int NumThreads, int Iterations, PerfCounter& pc);
}

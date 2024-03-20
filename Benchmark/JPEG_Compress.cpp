#include "JPEG_Compress.h"
#include <cmath>
#include <iostream>
using std::cout;

std::mutex mutex;
std::atomic<int> compressionCounter(0);

void JPEG_Compress::performIntensiveCalculation() {
    for (int i = 0; i < 5000000; ++i) {
        double result = sqrt(sin(cos(tan(0.12345))));
    }
}

void JPEG_Compress::compressJPEGThread(const char* inputFileName, const char* outputFileName, int quality, int iterations) {
    int width, height, channels;
    unsigned char* image = stbi_load(inputFileName, &width, &height, &channels, 3);
    cout << std::flush;

    if (!image) {
        std::cerr << "Error loading image in thread: " << stbi_failure_reason() << std::endl;
        return;
    }

    for (int i = 0; i < iterations; ++i) {
        // ģ������ܼ�������
        performIntensiveCalculation();

        stbi_write_jpg(outputFileName, width, height, channels, image, quality);
    }

    stbi_image_free(image);

    {
        std::lock_guard<std::mutex> lock(mutex);
        compressionCounter++;
    }
}

int JPEG_Compress::compressJPEG(const char* inputFileName, const char* outputFileName, int quality, int numThreads, int iterations) {
    // ��ʱ��ʼ
    clock_t startTime = clock();

    for (int i = 0; i < numThreads; ++i) {
        std::thread(compressJPEGThread, inputFileName, outputFileName, quality, iterations).detach();
    }

    // �ȴ������߳����
    while (compressionCounter < numThreads) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // ��ʱ����
    clock_t endTime = clock();
    double cpuTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    return EXIT_SUCCESS;
}

Tuple JPEG_Compress::JPEGCompTest(std::string Input, std::string Output, int Quality, int NumThreads, int Iterations, PerfCounter& pc)
{
    pc.reset();
    const char* InFile = Input.c_str(), * OutFile = Output.c_str();
    pc.start();
    compressJPEG(InFile, OutFile, Quality, NumThreads, Iterations);
    return pc.stop();
}
#pragma once
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <linux/perf_event.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <cstring>
#include <iostream>
#include <tuple>
#include <chrono>
using ll = long long;
using Tuple = std::tuple<ll, ll, ll>;

extern long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);

class PerfCounter 
{
public:
    PerfCounter();

    void start();
    std::tuple<ll, ll, ll> stop();
    void reset();

private:
    int fd_cycles, fd_instructions;
    struct perf_event_attr pe_cycles, pe_instructions;
    std::chrono::high_resolution_clock::time_point start_time;
};
#include "PerfCounter.h"

long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) 
{
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

PerfCounter::PerfCounter()
{
    memset(&pe_cycles, 0, sizeof(struct perf_event_attr));
    pe_cycles.type = PERF_TYPE_HARDWARE;
    pe_cycles.size = sizeof(struct perf_event_attr);
    pe_cycles.config = PERF_COUNT_HW_CPU_CYCLES;
    pe_cycles.disabled = 1;
    pe_cycles.exclude_kernel = 1;
    pe_cycles.exclude_hv = 1;

    memset(&pe_instructions, 0, sizeof(struct perf_event_attr));
    pe_instructions.type = PERF_TYPE_HARDWARE;
    pe_instructions.size = sizeof(struct perf_event_attr);
    pe_instructions.config = PERF_COUNT_HW_INSTRUCTIONS;
    pe_instructions.disabled = 1;
    pe_instructions.exclude_kernel = 1;
    pe_instructions.exclude_hv = 1;
}

void PerfCounter::start() 
{
    start_time = std::chrono::high_resolution_clock::now();
    
    fd_cycles = perf_event_open(&pe_cycles, 0, -1, -1, 0);
    fd_instructions = perf_event_open(&pe_instructions, 0, -1, -1, 0);
    if (fd_cycles == -1 || fd_instructions == -1) 
    {
        std::cerr << "Error in perf_event_open" << std::endl;
        exit(EXIT_FAILURE);
    }
    ioctl(fd_cycles, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_instructions, PERF_EVENT_IOC_RESET, 0);
    ioctl(fd_cycles, PERF_EVENT_IOC_ENABLE, 0);
    ioctl(fd_instructions, PERF_EVENT_IOC_ENABLE, 0);
}

Tuple PerfCounter::stop() 
{
    auto end_time = std::chrono::high_resolution_clock::now();
    ll duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    ioctl(fd_cycles, PERF_EVENT_IOC_DISABLE, 0);
    ioctl(fd_instructions, PERF_EVENT_IOC_DISABLE, 0);
    ll count_cycles, count_instructions;
    read(fd_cycles, &count_cycles, sizeof(long long));
    read(fd_instructions, &count_instructions, sizeof(long long));
    close(fd_cycles);
    close(fd_instructions);
    return std::make_tuple(count_cycles, count_instructions, duration);
}

void PerfCounter::reset()
{
    if (fd_cycles != -1) ioctl(fd_cycles, PERF_EVENT_IOC_RESET, 0);
    if (fd_instructions != -1) ioctl(fd_instructions, PERF_EVENT_IOC_RESET, 0);
}
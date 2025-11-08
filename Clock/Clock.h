#ifndef CLOCK_H
#define CLOCK_H

#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>

class Clock {
public:
    static std::atomic<uint64_t> cycles;
    static std::mutex clockMutex;
    static bool running;

    static void start(unsigned int tickMs = 0) {
        running = true;
        std::thread([tickMs]() {
            while (running) {
                {
                    std::lock_guard<std::mutex> lock(clockMutex);
                    ++cycles;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(tickMs));
            }
        }).detach();
    }

    static void stop() { running = false; }
    static uint64_t getCycle() { return cycles.load(); }
};

#endif

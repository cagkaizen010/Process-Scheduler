
#include "Clock.h"

std::atomic<uint64_t> Clock::cycles(0);
std::mutex Clock::clockMutex;
bool Clock::running = false;
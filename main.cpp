#include <cstdio>
#include <atomic>
#include <iostream>
#include <cstdlib>
#include <thread>

std::atomic<bool> is_running{true};

int main() {
	

	while (is_running) {

	}

	std::cout << "Exiting...";
	return 0;
}
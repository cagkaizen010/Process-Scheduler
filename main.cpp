#include <cstdio>
#include <atomic>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <unordered_map>

std::atomic<bool> is_running{true};

std::queue<std::string> command_queue;
std::mutex command_queue_mutex;

void keyboard_handler_thread_func() {
	std::string command_line;
	while(is_running){
		std::getline(std::cin, command_line);
		if(!command_line.empty()){
			std::unique_lock<std::mutex> lock(command_queue_mutex);
			command_queue.push(command_line);
			lock.unlock();
		}
	}
}

std::unordered_map<std::string, std::string> initialize() {
	std::string param;
	std::vector<std::string> params;
	std::ifstream file("config.txt");

	std::unordered_map<std::string, std::string> settings;

	if(!file) {
		std::cerr << "Could not open file." << std::endl;
		exit;
	}

	while(std::getline(file, param)) params.push_back(param);
	
	for(std::string p : params){
		std::vector<std::string> args;
		std::stringstream ss(p);
		// std::cout << p<< std::endl;
		
		while (ss >> p) {
			args.push_back(p);
		}

		settings[args.at(0)] = args.at(1); 	

	}

	return settings;
}

// --- Main Function (Command Interpreter Thread) ---
int main() {

	std::thread keyboard_handler_thread(keyboard_handler_thread_func);
	int cpuCycles = 0;

	initialize();

	while (is_running) {

		std::string command_line;
		{
			std::unique_lock<std::mutex> lock(command_queue_mutex);
			if(!command_queue.empty()){
				command_line = command_queue.front();
				command_queue.pop();
			}
		}

		if (!command_line.empty()){
			std::stringstream ss(command_line);
			std::vector<std::string> args;

			std::string temp;
			while(ss >> temp) args.push_back(temp);
			
			// for(const auto& i : args)
			// 	std::cout << i << std::endl;
		}

		cpuCycles++;
		std::cout << cpuCycles<< std::endl;

		// Slow down cycles for behavior observability.
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	std::cout << "Exiting...";
	return 0;
}
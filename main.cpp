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

#include "./Config/config.h"
#include "ConsoleUI/ConsoleUI.h"


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



int main() {
	ConsoleUI::initialize();
	ConsoleUI* consoleUI = ConsoleUI::getPtr();
	consoleUI->start();
	return 1;
}
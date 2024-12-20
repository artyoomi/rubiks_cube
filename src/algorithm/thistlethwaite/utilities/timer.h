#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <iostream>

class Timer {
public:
	// reset the timer
	void set()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	// get elapsed time
	double get()
	{
		auto end_point = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(_start).time_since_epoch().count();
		auto end   = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		return ms;
	}

    // get elapsed time and print the result with a message
	double get(const std::string& message)
	{
		double ms = this->get();

        std::cout << message << "(" << ms << "ms)." << std::endl;

		return ms;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

#endif // TIMER_H

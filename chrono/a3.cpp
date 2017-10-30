#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
/* 'Duration' is used for relative time. For absolute time,
 * 'timepoint' is used.
 *
 * A time point is nothing but a duration from the start of a certain
 * 'point'. So a duration from the start of Unix epoch is the current
 * absolute time.
 *
 * C++11 considers three clocks (representation for the start time),
 * system-clock, steady-clock and high-resolution clock.
 */

void print_system_clock_tp(std::chrono::system_clock::time_point &tp);

void print_steady_clock_tp(std::chrono::system_clock::time_point &tp);

int main()
{
	std::chrono::system_clock::time_point sys_now = std::chrono::system_clock::now();
	cout << "[system-clock] Current epoch: " << sys_now.time_since_epoch().count() << "\n";
	cout << "[system-clock] Current formatted time: ";
	print_system_clock_tp(sys_now);
	cout << "\n";

	std::chrono::steady_clock::time_point steady_now = std::chrono::steady_clock::now();
	cout << "[steady-clock] Current epoch: " << steady_now.time_since_epoch().count() << "\n";
	
}

/* Printing a timepoint takes a bit of conversion so creating a
 * function for this. */
void print_system_clock_tp(std::chrono::system_clock::time_point &tp)
{
	const time_t time = std::chrono::system_clock::to_time_t(tp);
	char str[100];
	std::strftime(str, sizeof(str), "%Y %B %d %H:%M", std::localtime(&time));
	cout << str;
}


#include <iostream>
#include <chrono>

using namespace std;
/** The chrono implements time handling. At its heart is the concept
 * of 'duration'. A duration is simply the count of number of ticks at
 * a certain interval. Conversion, comparison and artihmetic across
 * the various durations */

int main()
{
	/* Convenience helpers have been defined for the standard units, as below:
	 * std::chrono::milliseconds
	 * std::chrono::seconds
	 * std::chrono::minutes
	 * std::chrono:hours
	 * etc
	 */
	std::chrono::milliseconds one_second_as_milliseconds(1000);
	std::chrono::seconds one_second(1);

	/* The library automatically performs conversions for
	 * comparison operators */
	if (one_second_as_milliseconds == one_second) {
		cout << "Comparison across duration:\n";
		cout << "   This duration is the same\n";
		cout << "   one_second tick count  " << one_second.count() << "\n";
		cout << "   one_second_as_millisecons tick count  " << one_second_as_milliseconds.count() << "\n";
	}

	/* The library automatically performs conversion for
	 * arithmetic on durations */
	std::chrono::milliseconds three_seconds_as_milliseconds(3000);
	std::chrono::seconds four_seconds(4);
	auto result = four_seconds + three_seconds_as_milliseconds;
	cout << "Arithmetic across duration:\n";
	cout << "   The result is " << result.count() << "\n";

	/* The library automatically performs conversions for
	 * assignments
	 */
	std::chrono::seconds two_seconds(2);
	std::chrono::milliseconds two_seconds_as_milliseconds = two_seconds;
	if (two_seconds_as_milliseconds == two_seconds) {
		cout << "Assignment across duration:\n";
		cout << "   This duration is the same\n";
		cout << "   two_second tick count  " << two_seconds.count() << "\n";
		cout << "   two_second_as_millisecons tick count  " << two_seconds_as_milliseconds.count() << "\n";
	}


	std::chrono::milliseconds five_point_two_as_milliseconds(5200);
	std::chrono::seconds five_seconds;
	// Error: will lose the '.2' part of millisecond, explicit typecasting operator required
	//five_seconds = five_point_two_as_milliseconds;

	/* Use a casting operation for this, loses the .2 precision part */
	five_seconds = std::chrono::duration_cast<std::chrono::seconds> (five_point_two_as_milliseconds);
	/* Or use a duration where the tick count is a floating point, retains the precision part */
	std::chrono::duration<float, std::ratio<1, 1> > five_point_some_seconds = five_point_two_as_milliseconds;

	cout << "Assignment from high precision to low precision:\n";
	cout << "   With duration_cast, tick_count " << five_seconds.count() << "\n";
	cout << "   With floating ticks, tick_count " << five_point_some_seconds.count() << "\n";
}

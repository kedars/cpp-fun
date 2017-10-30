#include <iostream>
#include <chrono>

using namespace std;
/** The chrono implements time handling. At its heart is the concept
 * of 'duration'. A duration is simply the count of number of ticks at
 * a certain interval */

int main()
{
	/* What this says is the duration is 10. 
	 *   - But 10 of what?
	 *   - 10 of ratio 1/1000 of a second, i.e. milliseconds
	 *
	 * So this duration is 10 milliseconds
	 */
	std::chrono::duration<int, std::ratio<1, 1000> > ten_milli_sec_as_duration(10);

	/* Convenience helpers have been defined for the standard units, as below:
	 * std::chrono::milliseconds
	 * std::chrono::seconds
	 * std::chrono::minutes
	 * std::chrono:hours
	 * etc
	 */
	std::chrono::milliseconds ten_milli_sec(10);
	if (ten_milli_sec == ten_milli_sec_as_duration) {
		cout << "This duration is the same, and the tick count is " << ten_milli_sec.count() << "\n";
	}
}

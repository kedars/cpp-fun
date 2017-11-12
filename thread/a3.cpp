#include <iostream>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

/* Synchronising across multiple threads could be tricky. Use
 * std::future and std::promise to synchronize across multiple
 * threads.
 */
void time_consuming_operation(int delta, std::promise<int> my_promise)
{
	cout << "    time_consuming_thread: Performing time-consuming operation\n";
	/* Perform the time consuming operation */
	std::this_thread::sleep_for(std::chrono::seconds(4));

	cout << "    time_consuming_thread: notifying promise\n";
	/* Notify any waiters the value that is available */
	my_promise.set_value(delta);
}

int main()
{
	/* Create a promise, and get a 'future' variable from that
	 * promise. Now that promise and that future variable are tied
	 * together. A 'set_value' on promise notifies the 'future'.
	 */
	std::promise<int> result_promise;
	std::future<int> result_future = result_promise.get_future();

	cout << "main: Creating thread \n";
	std::thread long_operation(time_consuming_operation, 2, std::move(result_promise));
	/* The std::move above is required because 'promise' is not
	 * copyable. Only one entity can have ownership of a
	 * promise.
	 */

	cout << "main: Waiting on future \n";
	int result = result_future.get();
	cout << "main: The result is " << result << "\n";

	long_operation.join();
	return 0;
}


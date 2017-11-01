#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

/* Use std::mutex for locking between the threads */
int g_data;
std::mutex g_mux;

/* add 'delta' to g_data 100 times */
void adder(int delta = 1)
{
	for (int i = 0; i < 100; i++) {
		/* Lock guard acquires the lock in the constructor,
		 * and releases it in the destructor. So the lock gets
		 * acquired in this block */
		std::lock_guard<std::mutex> l(g_mux);
		g_data += delta;
		cout << "[adder] ++\n";
	}
}

/* subtract 'delta' from g_data 100 times */
void subtractor(int delta = 1)
{
	for (int i = 0; i < 100; i++) {
		std::lock_guard<std::mutex> l(g_mux);
		g_data -= delta;
		cout << "[subtractor] --\n";
	}
}

int main()
{
	/* Two ways of creating a thread: 
	 *
	 * The first argument to the constructor is the function name that should be run as a thread.
	 * The subsequent arguments are variable and passed directly to that function.
	 */
	std::thread ta(adder, 3);
	std::thread tb = std::thread(subtractor, 2);

	/* Wait for threads to finish */
	ta.join();
	tb.join();
	cout << "g_data is " << g_data << "\n" ;
}


#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

/* Create 2 threads and let them print something */
void a(int delta = 1)
{
	for (int i = 0; i < 100; i+= delta) {
		cout << "[a] " << i << "\n";
	}
}

void b(int delta = 1)
{
	for (int i = 100; i >= 0; i-= delta) {
		cout << "[b] " << i << "\n";
	}
}

int main()
{
	/* Two ways of creating a thread: 
	 *
	 * The first argument to the constructor is the function name that should be run as a thread.
	 * The subsequent arguments are variable and passed directly to that function.
	 */
	std::thread ta(a, 2);
	std::thread tb = std::thread(b, 5);

	/* Wait for threads to finish */
	ta.join();
	tb.join();
}


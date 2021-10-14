#include <iostream>
#include <thread>
#include <limits>

using namespace std;

const int N = 10;

bool b[N];
bool c[N];

int balance = 0;

int k = N/2;

const int TIMES = 100000;

void f(int i)
{
	for (int m = 0; m < TIMES; m++) {

L0:		b[i] = false;
L1:		if (k != i) {
L2:			c[i] = true;
L3:			if (b[k])
				k = i;
			goto L1;
		}
		else {
L4:			c[i] = false;
			for (int j = 0; j < N; j++)
				if (j != i && !c[j])
					goto L1;
		}
	
		// critical section begin
		balance++;
		// critical section end

		c[i] = true;
		b[i] = true;
	}

}

int main()
{
	cout << "int size: " << sizeof (int) << endl;
	cout << "Maximum value for int: " << numeric_limits<int>::max() << endl;
	
	for (int i = 0; i < N; i++) {
		b[i] = true;
		c[i] = true;
	}

	thread* workers[N];
	for (int i = 0; i < N; i++) {
		workers[i] = new thread{f, i};
	}		

	for (int i = 0; i < N; i++) {
		workers[i]->join();
	}		
	
    cout << "balance: " << balance << endl;
    cout << "which should be: " << TIMES * N << endl;
    return 0;
}

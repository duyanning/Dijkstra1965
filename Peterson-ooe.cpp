#include <iostream>
#include <thread>
#include <atomic>
#include <limits>

using namespace std;

int balance = 0;

//const int TIMES = 100000;
const int TIMES = 100000;

//bool t1, t2;
atomic<bool> t1, t2;
//int t;
atomic<int> t;

void f1()
{
	for (int m = 0; m < TIMES; m++) {

		t1 = true;
		t = 2;
		while(t2==true && t==2)
			;
	
		// critical section begin
		balance++;
		// critical section end

		t1 = false;
	}

}

void f2()
{
	for (int m = 0; m < TIMES; m++) {

		t2 = true;
		t = 1;
		while(t1==true && t==1)
			;
	
		// critical section begin
		balance++;
		// critical section end

		t2 = false;
	}

}

int main()
{
	cout << "int size: " << sizeof (int) << endl;
	cout << "Maximum value for int: " << numeric_limits<int>::max() << endl;
	
	thread* workers[1+2];
	workers[0] = nullptr;
	workers[1] = new thread{f1};
	workers[2] = new thread{f2};

	workers[1]->join();
	workers[2]->join();
	
    cout << "balance: " << balance << endl;
    cout << "which should be: " << TIMES * 2 << endl;
    return 0;
}

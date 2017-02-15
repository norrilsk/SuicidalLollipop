#include <bits/stdc++.h>
#include <thread>
#include <mutex> 
using namespace std;

std::mutex mtx; 

void make_good(double(*func)(double), int n, double lower, double upper, double left, double right, int *res) 
{
	mt19937 gen(rand());
	uniform_real_distribution<double> disA(lower,upper);
	uniform_real_distribution<double> disB(left, right);
	int local_res = 0;
	for(int i = 0; i < n; ++i)
	{
		double x = disB(gen);
		double y = disA(gen);
		double f = func(x);
		if(y > 0 && f > y)
			 ++local_res;
		if(y < 0 &&  f< y)
			--local_res;
	}
	// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	//cout << "tread result" << double(local_res) / n * (upper - lower) *(right - left) << endl;
	*res += local_res;
	mtx.unlock();
}

double funct(double x)
{
	return x*x*sin(1/(x*x*x*x));
}

int main ()
{
	srand(time(NULL));
	time_t t = time(NULL);
	double sig = 0;
	int N = 4;
	int n = 16000000;
	double a = 0, b = 0.9, m = -1, M = 1;
	int res = 0;  
	std::vector<thread> workers;
	for (int i = 0; i < N; i++) {
		workers.push_back(thread(make_good, funct, n, m, M, a, b, &res));
	}
	std::for_each(workers.begin(), workers.end(), [](thread &t) 
	{
		t.join();
	});
	double fin = double(res)/double(N*n)*(b -a)*(M - m);
	cout.precision(6);
	cout << "RESULT:  "<< fin << endl;
	cout << "Wolfram: " << 0.0503993 << endl;
	sig += fabs(fin - 0.0503993);
	cout.precision(2);
	cout <<"Error: "<<sig / 0.0503993 * 100 <<"%"<< endl;
	cout << "Total time:" <<time(NULL) -t <<"sec"<<endl;
	return 0;
}

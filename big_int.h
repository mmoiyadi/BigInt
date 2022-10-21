#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>


using namespace std;

struct big_int {
	void init(string s);
	big_int(string s);
	big_int(int s);

	big_int();

	big_int(const big_int& other);

	big_int& operator=(const big_int& other);

	friend ostream& operator << (ostream& os, big_int b);

	string to_string() const;

	void trim();

	int size() const;

	void multiply_by_ten_power(int power);

	bool is_zero();

	// Split the integer into two halves and return a pair
	pair<big_int, big_int> split() const;

	// The multiplication is implemented using the Karatsuba algorithm (divide and conquer approach)
	big_int multiply(const big_int& other, int size) const;

	void normalize(big_int& a, big_int& b) const ;

	// The multiplication is implemented using the Karatsuba algorithm (divide and conquer approach)
	big_int operator * (const big_int& other) const;

	big_int operator +(const big_int& other);

private:
	void add_digit(int d);
	vector<int> v;
	
};

class big_int_operations {
public:	
	big_int fibonacci(int n);
	big_int factorial(int n);
private:
	big_int fib(int n, vector< big_int >& f);
	big_int fact(int n, vector< big_int >& f);
};

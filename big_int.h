#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>


using namespace std;

struct BigInt {
	void init(string s);
	BigInt(string s);

	BigInt();

	BigInt(const BigInt& other);

	BigInt& operator=(const BigInt& other);

	friend ostream& operator << (ostream& os, BigInt b);

	string toString() const;

	void trim();

	int size() const;

	void multiplyByTenPower(int power);

	bool isZero();

	pair<BigInt, BigInt> split() const;

	BigInt multiply(const BigInt& other, int size) const;

	// The multiplication is implemented using the Karatsuba algorithm (divide and conquer approach)
	BigInt operator * (const BigInt& other) const;

	BigInt operator +(const BigInt& other);

private:
	void addDigit(int d);
	vector<int> v;
	
};

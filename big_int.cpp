#include "big_int.h"
#include <future>
#include <cmath>
ostream& operator << (ostream& os, big_int b)
{
	os << b.to_string();
	return os;
}

void big_int::init(string s) {
	bool isNumber = !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	if (isNumber) {
		for (auto c = s.rbegin(); c != s.rend(); c++) {
			v.push_back(*c - 48);
		}
	}
}

big_int::big_int(string s) {
	init(s);
}

big_int::big_int(int n)
{
	auto div = n;
	int no_digits = 0;
	while (div != 0) {
		div /= 10;
		no_digits++;
	}
	div = n;
	while (no_digits) {
		auto rem = div % 10;
		div /= 10;
		v.push_back(rem);
		no_digits--;
	}
	//init(std::to_string(n));
}

big_int::big_int() {

}

big_int::big_int(const big_int& other) {
	string sOther = other.to_string();
	init(sOther);
}

string big_int::to_string() const {
	string ret;
	if (!v.empty()) {
		for (auto i = v.rbegin(); i != v.rend(); i++) {
			ret.push_back(*i + 48);
		}
	}

	return ret;
}

void big_int::trim() {
	if (!v.empty()) {
		auto i = v.end() - 1;
		while (*i == 0) {
			v.erase(i);
			i = v.end() - 1;
		}
	}
}

int big_int::size() const {
	return v.size();
}

void big_int::multiply_by_ten_power(int power) {
	for (auto i = 0; i < power; i++) {
		v.insert(v.begin(), 0);
	}
}

bool big_int::is_zero() {
	return v.empty() || all_of(v.begin(), v.end(), [](int n) {return n == 0; });
}

pair<big_int, big_int> big_int::split() const {
	int sz = size();
	if (sz == 1) {
		return make_pair(big_int(), big_int(*this));
	}
	else {
		big_int left, right;
		auto it = v.begin();
		auto offset = ceil((double)sz / 2);
		auto mid = v.begin() + offset;
		for (; it != mid; ++it) {
			left.add_digit(*it);
			if (it + offset != v.end())
				right.add_digit(*(it + offset));
		}
		return make_pair(right, left);
	}

}

big_int big_int::multiply(const big_int& other, int size) const {
	big_int ret;
	if (size == 1) {
		auto res = v[0] * other.v[0];
		if (res > 9) {
			auto div = res / 10;
			res = res % 10;
			ret.add_digit(res);
			ret.add_digit(div);
		}
		else {
			ret.add_digit(res);
		}

	}
	else {
		auto ab = split();
		auto a = ab.first;
		auto b = ab.second;
		auto cd = other.split();
		auto c = cd.first;
		auto d = cd.second;
		normalize(a, c);
		//auto first = a.multiply(c, c.size());

		auto first = async(std::launch::async, &big_int::multiply, &a, c, c.size());
		//auto first = a * c;
		auto sz = size % 2 == 0 ? size : size + 1;

		auto ad = a * d;
		auto bc = b * c;
		auto second = ad + bc;
		second.multiply_by_ten_power(sz / 2);
		auto third = b * d;
		//auto first_val = first;
		auto first_val = first.get();
		first_val.multiply_by_ten_power(sz);
		ret = first_val + second + third;

	}
	return ret;
}

void big_int::normalize(big_int& a, big_int& b) const {
	if (b.size() > a.size()) {
		auto diff = b.size() - a.size();
		for (auto i = 0; i < diff; i++) {
			a.add_digit(0);
		}
	}
	else {
		auto diff = a.size() - b.size();
		for (auto i = 0; i < diff; i++) {
			b.add_digit(0);
		}
	}
}

void big_int::add_digit(int d) {
	v.push_back(d);
}

big_int big_int::operator*(const big_int& other) const {
	big_int b1(*this);
	big_int b2(other);
	// pad smaller int with leading zeroes to make both int of same size
	if (b1.size() > b2.size()) {
		auto diff = b1.size() - b2.size();
		for (auto i = 0; i < diff; i++) {
			b2.add_digit(0);
		}
	}
	else {
		auto diff = b2.size() - b1.size();
		for (auto i = 0; i < diff; i++) {
			b1.add_digit(0);
		}
	}
	return b1.multiply(b2, b1.size());
}

big_int& big_int::operator=(const big_int& other) {
	v.clear();
	init(other.to_string());
	return *this;
}

big_int big_int::operator +(const big_int& other) {
	big_int ret;
	int carry = 0;
	auto it1b = v.begin(), it1e = v.end();
	auto it2b = other.v.begin(), it2e = other.v.end();
	while (it1b != it1e || it2b != it2e) {
		auto f = (it1b == it1e) ? 0 : *it1b;
		auto s = (it2b == it2e) ? 0 : *it2b;
		int res = f + s + carry;
		if (res > 9) {
			res = res % 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
		ret.add_digit(res);
		if (it1b != it1e)
			++it1b;
		if (it2b != it2e)
			++it2b;
	}

	if (carry > 0) {
		ret.add_digit(carry);
	}
	return ret;
}

big_int big_int_operations::fib(int n, vector< big_int >& f) {
	f[0] = big_int("0");
	f[1] = big_int("1");
	for (auto i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	return f[n];
}


big_int big_int_operations::fibonacci(int n) {
	vector<big_int> v(max(2, n + 1));
	big_int f = fib(n, v);
	return f;
}

big_int big_int_operations::factorial(int n)
{
	vector<big_int> v(max(2, n + 1));
	big_int f = fact(n, v);
	return f;
}

big_int big_int_operations::fact(int n, vector<big_int>& f)
{
	f[0] = big_int("1");
	f[1] = big_int("1");
	for (auto i = 2; i <= n; i++) {
		f[i] = f[i - 1] * i;;
	}
	return f[n];
}
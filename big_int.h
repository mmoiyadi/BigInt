#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>


using namespace std;

struct BigInt {
	void init(string s) {
		bool isNumber = !s.empty() && std::find_if(s.begin(),
			s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
		if (isNumber) {
			for (auto c = s.rbegin(); c != s.rend(); c++) {
				v.push_back(*c - 48);
			}
		}
	}
	BigInt(string s) {
		init(s);
	}

	BigInt() {

	}

	BigInt(const BigInt& other) {
		string sOther = other.getIntAsString();
		init(sOther);
	}

	BigInt& operator=(const BigInt& other) {
		v.clear();
		init(other.getIntAsString());
		return *this;
	}

	friend ostream& operator << (ostream& os, BigInt b);

	string getIntAsString() const  {
		string ret;
		if (!v.empty()) {
			for (auto i = v.rbegin(); i != v.rend(); i++) {
				ret.push_back(*i + 48);
			}
		}
		
		return ret;
	}

	void trim() {
		if (!v.empty()) {
			auto i = v.end()-1;
			while (*i == 0) {
				v.erase(i);
				i = v.end()-1;
			}
		}
	}

	int size() const  {
		return v.size();
	}

	void multiplyByTenPower(int power) {
		for (auto i = 0; i < power; i++) {
			v.insert(v.begin(), 0);
		}
	}

	bool isZero() {
		return v.empty() || all_of(v.begin(), v.end(), [](int n) {return n == 0; });
	}

	pair<BigInt, BigInt> split() const {
		int sz = size();
		if (sz == 1) {
			return make_pair(BigInt(), BigInt(*this));
		}
		else {
			BigInt left,right;
			auto it = v.begin();
			auto offset = ceil((double)sz / 2);
			auto mid = v.begin() + offset ;
			for (; it != mid; ++it) {
				left.addDigit(*it);
				if(it + offset != v.end())
					right.addDigit(*(it + offset));
			}
			return make_pair(right, left);
		}

	}

	BigInt multiply(const BigInt& other, int size) const {
		BigInt ret;
		int carry = 0;
		if (size == 1) {
			auto res = v[0] * other.v[0];
			if (res > 9) {
				auto div = res / 10;
				res = res % 10;
				ret.addDigit(res);
				ret.addDigit(div);
			}
			else {
				ret.addDigit(res);
			}

		}
		else {
			auto ab = split();
			auto a = ab.first;
			auto b = ab.second;
			auto cd = other.split();
			auto c = cd.first;
			auto d = cd.second;
			auto first = a * c;
			auto sz = size % 2 == 0 ? size : size + 1;
			first.multiplyByTenPower(sz);
			auto ad = a * d;
			auto bc = b * c;
			auto second = ad + bc;
			second.multiplyByTenPower(sz / 2);
			auto third = b * d;
			ret = first + second + third;

		}
		return ret;
	}

	BigInt operator * (const BigInt& other) const {
		BigInt b1(*this);
		BigInt b2(other);
		// pad smaller int with leading zeroes to make both int of same size
		if (b1.size() > b2.size()) {
			auto diff = b1.size() - b2.size();
			for (auto i = 0; i < diff; i++) {
				b2.addDigit(0);
			}
		}
		else {
			auto diff = b2.size() - b1.size();
			for (auto i = 0; i < diff; i++) {
				b1.addDigit(0);
			}
		}
		return b1.multiply(b2, b1.size());
	}

	BigInt operator +(const BigInt& other) {
		auto len = min(size(), other.size());
		BigInt ret;
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
			ret.addDigit(res);
			if (it1b != it1e)
				++it1b;
			if (it2b != it2e)
				++it2b;
		}
		
		if (carry > 0) {
			ret.addDigit(carry);
		}
		return ret;
	}

private:
	void addDigit(int d) {
		v.push_back(d);
	}
	vector<int> v;
	
};

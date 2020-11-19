#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "big_int.h"
ostream& operator << (ostream& os, BigInt b)
{
	os << b.toString();
	return os;
}

void BigInt::init(string s) {
	bool isNumber = !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	if (isNumber) {
		for (auto c = s.rbegin(); c != s.rend(); c++) {
			v.push_back(*c - 48);
		}
	}
}

BigInt::BigInt(string s) {
	init(s);
}

BigInt::BigInt() {

}

BigInt::BigInt(const BigInt& other) {
	string sOther = other.toString();
	init(sOther);
}

string BigInt::toString() const {
	string ret;
	if (!v.empty()) {
		for (auto i = v.rbegin(); i != v.rend(); i++) {
			ret.push_back(*i + 48);
		}
	}

	return ret;
}

void BigInt::trim() {
	if (!v.empty()) {
		auto i = v.end() - 1;
		while (*i == 0) {
			v.erase(i);
			i = v.end() - 1;
		}
	}
}

int BigInt::size() const {
	return v.size();
}

void BigInt::multiplyByTenPower(int power) {
	for (auto i = 0; i < power; i++) {
		v.insert(v.begin(), 0);
	}
}

bool BigInt::isZero() {
	return v.empty() || all_of(v.begin(), v.end(), [](int n) {return n == 0; });
}

pair<BigInt, BigInt> BigInt::split() const {
	int sz = size();
	if (sz == 1) {
		return make_pair(BigInt(), BigInt(*this));
	}
	else {
		BigInt left, right;
		auto it = v.begin();
		auto offset = ceil((double)sz / 2);
		auto mid = v.begin() + offset;
		for (; it != mid; ++it) {
			left.addDigit(*it);
			if (it + offset != v.end())
				right.addDigit(*(it + offset));
		}
		return make_pair(right, left);
	}

}

BigInt BigInt::multiply(const BigInt& other, int size) const {
	BigInt ret;
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

void BigInt::addDigit(int d) {
	v.push_back(d);
}

BigInt BigInt::operator*(const BigInt& other) const {
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

BigInt& BigInt::operator=(const BigInt& other) {
	v.clear();
	init(other.toString());
	return *this;
}

BigInt BigInt::operator +(const BigInt& other) {
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

TEST_CASE("Integers are multiplied correctly", "[product]") {
	SECTION("multiply big integers") {
		BigInt b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		BigInt b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.toString() == "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");
	}

	SECTION("multiply small integers") {
		BigInt b1{ "3" };
		BigInt b2{ "2" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.toString() == "6");
	}

	SECTION("multiply mid sized integers") {
		BigInt b1{ "98346" };
		BigInt b2{ "248356" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.toString() == "24424819176");
	}
	SECTION("multiply mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "59870263341" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.toString() == "1462320356123426627016");
	}
	SECTION("multiply mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "5987026" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.toString() == "146232027452010576");
	}
}

TEST_CASE("Integers are added correctly", "[sum]") {
	SECTION("sum big integers") {
		BigInt b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		BigInt b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.toString() == "5859874482048838473822930854632165381954416493075065395941912219");
	}

	SECTION("sum small integers") {
		BigInt b1{ "3" };
		BigInt b2{ "2" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.toString() == "5");
	}

	SECTION("sum mid sized integers") {
		BigInt b1{ "98346" };
		BigInt b2{ "248356" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.toString() == "346702");
	}
	SECTION("sum mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "59870263341" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.toString() == "84295082517");
	}
	SECTION("sum mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "5987026" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.toString() == "24430806202");
	}
}

TEST_CASE("Test for zero integers", "[zero]") {
	SECTION("zero test 1") {
		BigInt b1;
		REQUIRE(b1.isZero() == true);
	}
	SECTION("zero test 2") {
		BigInt b1("");
		REQUIRE(b1.isZero() == true);
	}
	SECTION("zero test 3") {
		BigInt b1("00000000000000000000000000000000000000000000000000000000000000000000000");
		REQUIRE(b1.isZero() == true);
	}
	SECTION("non-zero test 1") {
		BigInt b1("00000000000000000000000000000000000000000000000000000000000000000000001");
		REQUIRE(b1.isZero() == false);
	}
	SECTION("non-zero test 2") {
		BigInt b1("0001000");
		REQUIRE(b1.isZero() == false);
	}
	SECTION("non-zero test 3") {
		BigInt b1("01234567890");
		REQUIRE(b1.isZero() == false);
	}
}


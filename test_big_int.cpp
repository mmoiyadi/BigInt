#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "big_int.h"
ostream& operator << (ostream& os, BigInt b)
{
	os << b.getIntAsString();
	return os;
}

TEST_CASE("Integers are multiplied correctly", "[product]") {
	SECTION("multiply big integers") {
		BigInt b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		BigInt b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.getIntAsString() == "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");
	}

	SECTION("multiply small integers") {
		BigInt b1{ "3" };
		BigInt b2{ "2" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.getIntAsString() == "6");
	}

	SECTION("multiply mid sized integers") {
		BigInt b1{ "98346" };
		BigInt b2{ "248356" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.getIntAsString() == "24424819176");
	}
	SECTION("multiply mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "59870263341" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.getIntAsString() == "1462320356123426627016");
	}
	SECTION("multiply mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "5987026" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.getIntAsString() == "146232027452010576");
	}
}

TEST_CASE("Integers are added correctly", "[sum]") {
	SECTION("sum big integers") {
		BigInt b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		BigInt b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.getIntAsString() == "5859874482048838473822930854632165381954416493075065395941912219");
	}

	SECTION("sum small integers") {
		BigInt b1{ "3" };
		BigInt b2{ "2" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.getIntAsString() == "5");
	}

	SECTION("sum mid sized integers") {
		BigInt b1{ "98346" };
		BigInt b2{ "248356" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.getIntAsString() == "346702");
	}
	SECTION("sum mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "59870263341" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.getIntAsString() == "84295082517");
	}
	SECTION("sum mid sized integers") {
		BigInt b1{ "24424819176" };
		BigInt b2{ "5987026" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.getIntAsString() == "24430806202");
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


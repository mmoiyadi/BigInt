#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "big_int.h"


TEST_CASE("Factorial") {
	SECTION("Factorial") {
		big_int_operations bio;
		auto fact0 = bio.factorial(0);
		auto fact1 = bio.factorial(1);
		auto fact2 = bio.factorial(2);
		auto fact5 = bio.factorial(5);
		auto fact10 = bio.factorial(10);
		fact10.trim();
		auto fact11 = bio.factorial(11);
		fact11.trim();
		auto fact12 = bio.factorial(12);
		fact12.trim();
		//auto fact20 = bio.factorial(20);
		//fact20.trim();
		/*auto fact50 = bio.factorial(50);
		auto fact100 = bio.factorial(100);
		auto fact200 = bio.factorial(200);
		auto fact300 = bio.factorial(300);*/

		REQUIRE(fact0.to_string() == "1");
		REQUIRE(fact1.to_string() == "1");
		REQUIRE(fact2.to_string() == "2");
		REQUIRE(fact5.to_string() == "120");
		REQUIRE(fact10.to_string() == "3628800");
		REQUIRE(fact11.to_string() == "39916800");
		REQUIRE(fact12.to_string() == "479001600");
		//REQUIRE(fact30.to_string() == "265252859812191058636308480000000");
		/*REQUIRE(fact50.to_string() == "12586269025");
		REQUIRE(fact100.to_string() == "354224848179261915075");
		REQUIRE(fact200.to_string() == "280571172992510140037611932413038677189525");
		REQUIRE(fact300.to_string() == "222232244629420445529739893461909967206666939096499764990979600");*/
	}
}
TEST_CASE("Fibonacci") {
	SECTION("Fibonacci") {
		big_int_operations bio;
		auto fib0 = bio.fibonacci(0);
		auto fib1 = bio.fibonacci(1);
		auto fib2 = bio.fibonacci(2);
		auto fib5 = bio.fibonacci(5);
		auto fib10 = bio.fibonacci(10);
		auto fib50 = bio.fibonacci(50);
		auto fib100 = bio.fibonacci(100);
		auto fib200 = bio.fibonacci(200);
		auto fib300 = bio.fibonacci(300);

		REQUIRE(fib0.to_string() == "0");
		REQUIRE(fib1.to_string() == "1");
		REQUIRE(fib2.to_string() == "1");
		REQUIRE(fib5.to_string() == "5");
		REQUIRE(fib10.to_string() == "55");
		REQUIRE(fib50.to_string() == "12586269025");
		REQUIRE(fib100.to_string() == "354224848179261915075");
		REQUIRE(fib200.to_string() == "280571172992510140037611932413038677189525");
		REQUIRE(fib300.to_string() == "222232244629420445529739893461909967206666939096499764990979600");
	}

	
}


TEST_CASE("Test integers are multiplied correctly", "[product]") {
SECTION("product test: big integers") {
		big_int b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		big_int b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto start_time = chrono::high_resolution_clock::now();
		auto product = b1 * b2;
		product.trim();
		auto total_time = chrono::high_resolution_clock::now() - start_time;
		REQUIRE(product.to_string() == "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");
	}

	SECTION("product test: small integers") {
		big_int b1{ "3" };
		big_int b2{ "2" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.to_string() == "6");
	}

	SECTION("product test: mid sized integers") {
		big_int b1{ "98346" };
		big_int b2{ "248356" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.to_string() == "24424819176");
	}
	SECTION("product test: mid sized integers 2") {
		big_int b1{ "24424819176" };
		big_int b2{ "59870263341" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.to_string() == "1462320356123426627016");
	}
  SECTION("product test: mid sized integers 3") {
		big_int b1{ "123456789" };
		big_int b2{ "987654321" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.to_string() == "121932631112635269");
	}
	SECTION("product test: mid sized integers 3") {
		big_int b1{ "24424819176" };
		big_int b2{ "5987026" };
		auto product = b1 * b2;
		product.trim();
		REQUIRE(product.to_string() == "146232027452010576");
	}
  SECTION("product test: multiplication with zero is zero") {
		big_int num{ "24424819176" };
		big_int zero;
		auto product = num * zero;
		product.trim();
		REQUIRE(product.is_zero());
	}
  SECTION("product test: multiplication with one is same number") {
		big_int num{ "24424819176" };
		big_int one{"1"};
		auto product = num * one;
		product.trim();
		REQUIRE(product.to_string() == num.to_string());
	}
  SECTION("product test: multiplication with ten") {
		big_int num{ "24424819176" };
		big_int one{"10"};
		auto product = num * one;
		product.trim();
    num.multiply_by_ten_power(1);
    num.trim();
		REQUIRE(product.to_string() == num.to_string());
	}
  SECTION("product test: multiplication with hundred") {
		big_int num{ "24424819176" };
		big_int one{"100"};
		auto product = num * one;
		product.trim();
    num.multiply_by_ten_power(2);
    num.trim();
		REQUIRE(product.to_string() == num.to_string());
	}
  SECTION("product test: multiplication with thousand") {
		big_int num{ "24424819176" };
		big_int one{"1000"};
		auto product = num * one;
		product.trim();
    num.multiply_by_ten_power(3);
    num.trim();
		REQUIRE(product.to_string() == num.to_string());
	}
}

TEST_CASE("Test integers are added correctly", "[sum]") {
	SECTION("sum: big integers") {
		big_int b1{ "3141592653589793238462643383279502884197169399375105820974944592" };
		big_int b2{ "2718281828459045235360287471352662497757247093699959574966967627" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.to_string() == "5859874482048838473822930854632165381954416493075065395941912219");
	}

	SECTION("sum test: small integers") {
		big_int b1{ "3" };
		big_int b2{ "2" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.to_string() == "5");
	}

	SECTION("sum test: mid sized integers") {
		big_int b1{ "98346" };
		big_int b2{ "248356" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.to_string() == "346702");
	}
	SECTION("sum: mid sized integers 2") {
		big_int b1{ "24424819176" };
		big_int b2{ "59870263341" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.to_string() == "84295082517");
	}
	SECTION("sum: mid sized integers 3") {
		big_int b1{ "24424819176" };
		big_int b2{ "5987026" };
		auto sum = b1 + b2;
		sum.trim();
		REQUIRE(sum.to_string() == "24430806202");
	}
  SECTION("sum: sum with zero is same number") {
		big_int num{ "24424819176" };
		big_int zero;
		auto sum = num + zero;
		sum.trim();
		REQUIRE(sum.to_string() == num.to_string());
	}
  SECTION("sum: sum with same number is product of number with two") {
		big_int num{ "24424819176" };
		big_int two{"2"};
		auto sum_with_num = num + num;
		sum_with_num.trim();
    auto product_with_two = num * two;
    product_with_two.trim();
		REQUIRE(sum_with_num.to_string() == product_with_two.to_string());
	}
}

TEST_CASE("Test for zero integers", "[zero]") {
	SECTION("zero test: no value is zero") {
		big_int b1;
		REQUIRE(b1.is_zero() == true);
	}
	SECTION("zero test: empty string is zero") {
		big_int b1("");
		REQUIRE(b1.is_zero() == true);
	}
	SECTION("zero test: all zeros is zero") {
		big_int b1("00000000000000000000000000000000000000000000000000000000000000000000000");
		REQUIRE(b1.is_zero() == true);
	}
	SECTION("non-zero test: leading zeros followed by non-zero is non-zero") {
		big_int b1("00000000000000000000000000000000000000000000000000000000000000000000001");
		REQUIRE(b1.is_zero() == false);
	}
	SECTION("non-zero test: leading zeros followed by non-zero followed by zeros is non-zero") {
		big_int b1("0001000");
		REQUIRE(b1.is_zero() == false);
	}
	SECTION("non-zero test: non-zero value is non-zero") {
		big_int b1("01234567890");
		REQUIRE(b1.is_zero() == false);
	}
}
#ifdef RUN_ALL_TESTS
#endif
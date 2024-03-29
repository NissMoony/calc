#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>
#include "../src/Parser.h"
#include "../src/Parser.cpp"

inline double round4(double num) {
    return round(num * 10000) / 10000;
}

bool test(const char *input, double expected) {
    try {
        Parser parser(input);
        double result = round4(Solve(parser.Parse()));
        if (result == expected) return true;
        std::cout << input << " = " << expected << " : error, got " << result << '\n';
    }
    catch (std::exception &e) {
        std::cout << input << " : exception: " << e.what() << '\n';
    }
    return false;
}

TEST_CASE("simple arithmetic") {
    CHECK(test("9", 9));
    CHECK(test("10", 10));
    CHECK(test("+1", 1));
    CHECK(test("-1", -1));
    CHECK(test("(1)", 1));
    CHECK(test("(-1)", -1));
    CHECK(test("abs(-1)", 1));
    CHECK(test("1+20", 21));
    CHECK(test("1 + 20", 21));
    CHECK(test("1+20+300+4000", 4321));
    CHECK(test("-1+20", 19));
    CHECK(test("--1+20", 21));
    CHECK(test("---1+20", 19));
    CHECK(test("(1+20)", 21));
    CHECK(test("-2*3", -6));
    CHECK(test("2*-3", -6));
    CHECK(test("1++2", 3));
    CHECK(test("1+10*2", 21));
    CHECK(test("10*2+1", 21));
    CHECK(test("(1+20)*2", 42));
    CHECK(test("2*(1+20)", 42));
    CHECK(test("(1+2)*(3+4)", 21));
    CHECK(test("2*3+4*5", 26));
    CHECK(test("100+2*10+3", 123));
    CHECK(test("2^3", 8));
    CHECK(test("2^3*5+2", 42));
    CHECK(test("5*2^3+2", 42));
    CHECK(test("2+5*2^3", 42));
    CHECK(test("1+2^3*10", 81));
    CHECK(test("2^3+2*10", 28));
    CHECK(test("5 * 4 + 3 * 2 + 1", 27));
    CHECK(test("2.5", 2.5));
    CHECK(test("3 % 2", 1));
    CHECK(test("(12+34  -+5)", 41));
}

TEST_CASE("math functions") {
    CHECK(test("sin(2)", 0.9093));
    CHECK(test("cos(3^3)", -0.2921));
    CHECK(test("sin(cos(10))", -0.7440));
    CHECK(test("sin(5)*cos(5)", -0.2720));
    CHECK(test("ln(5)", 1.6094));
    CHECK(test("lg(15)", 1.1761));
    CHECK(test("asin(0.3)", 0.3047));
    CHECK(test("acos(0.7)", 0.7954));
    CHECK(test("tan(55)", -45.1831));
    CHECK(test("atan(5)", 1.3734));
}

TEST_CASE("errors") {
    CHECK(!test("2..5", 0));
    CHECK(!test("si7", 0));
    CHECK(!test("(5*sin(5)", 0));
    CHECK(!test("asin(5)", 0));
}
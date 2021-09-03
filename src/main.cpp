//
// Created by cotsm on 14/07/2021.
//


#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <map>
#include "../inc/streampp.h"

class B {

    void display() {
        std::cout << _v << std::endl;
    }

public:
    explicit B(int value) : _v(value + 'A') {}

    char _v;
};

class A {

public:
    explicit A(int value) : _v(value) {}

    int _v;

    int value() const { return _v; }

    bool isOdd() const {
        return _v % 2 == 0;
    }

    void time_two() {
        _v += _v;
    }

    bool isEven() const {
        return !isOdd();
    }

    bool isEven() {
        return !isOdd();
    }

    B &getChar() const {
        B *b = new B(_v);
        return *b;
    }

    bool isNegative() const {
        return _v < 0;
    }

    bool isPositive() const {
        return !isNegative();
    }

    void display() {
        std::cout << _v << " from A" << std::endl;
    }
};

void displayB(B &item) {
    std::cout << item._v << std::endl;
}

void display(A &item) {
    std::cout << item._v << std::endl;
}

B &getChar(A &item) {
    return item.getChar();
}

bool foo(A &item) {
    return item.isOdd();
}

using namespace streampp;

int main() {

    std::vector<A> vector_data;
    int size = 1000000;
    vector_data.reserve(size);
    for (int i = 0; i < size; i++)
        vector_data.emplace_back(i);

    std::cout << "STREAM ---" << std::endl;
    auto start = std::chrono::steady_clock::now();

    auto stream_ptr = StreamBuilder<A>::make(vector_data);
    auto stream_result = stream_ptr
                        ->limit(20)
                        ->collectToVector();

    std::for_each(stream_result.begin(), stream_result.end(), display);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return EXIT_SUCCESS;
}


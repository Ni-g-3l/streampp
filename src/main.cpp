//
// Created by cotsm on 14/07/2021.
//


#include <iostream>
#include <vector>
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

    bool isOdd() const {
        return _v % 2 == 0;
    }

    bool isEven() const {
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
        std::cout << _v << std::endl;
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

using namespace streampp;

int main() {

    std::vector<A> data;
    int size = 100;
    data.reserve(size);
    for (int i = 0; i < size; i++)
        data.emplace_back(A(i));

    std::cout << "For each Lambda -------------------------" << std::endl;
    auto *stream = Stream<A>::make(data);
    std::cout << stream->filter(&A::isOdd)->count() << std::endl;
    return 0;
}


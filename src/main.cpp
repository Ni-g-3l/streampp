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
        std::cout << _v  << " from A" << std::endl;
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
    int size = 100;
    vector_data.reserve(size);
    for (int i = 0; i < size; i++)
        vector_data.emplace_back(i);

    std::cout << "STREAM ---" << std::endl;
    auto start = std::chrono::steady_clock::now();

    auto stream_ptr = StreamBuilder<A>::make(vector_data);
    stream_ptr->filter(&A::isOdd)
                ->map(&A::time_two)
                ->forEach(&A::display);

    long count = StreamBuilder<A>::make(vector_data)->count();
    std::cout << "Count : " << count << std::endl;

    stream_ptr = StreamBuilder<A>::make(vector_data);
    stream_ptr->limit(10)
              ->forEach(&A::display);


    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double>  elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    start = std::chrono::steady_clock::now();
    std::cout << "FOR EACH ---" << std::endl;
    for(auto & a : vector_data) {
        if (a.isOdd()){
            a.time_two();
            a.display();
        }
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";


    return EXIT_SUCCESS;
}


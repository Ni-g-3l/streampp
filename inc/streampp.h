
#ifndef _STREAMPP_H_
#define _STREAMPP_H_

#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

namespace streampp {

    template<typename T>
    class Stream {

        template<typename R>
        class Builder {
        public:
            void accept(R &t) {

            }

            Stream::Builder<R> *add(R &t) {
                accept(t);
                return this;
            }

            Stream<R> *build() {
                new Stream<T>();
            }
        };

    public:

        Stream() {

        }

        bool allMatch(std::function<bool(T &)> f) {
            return false;
        }

        bool anyMatch(std::function<bool(T &)> f) {
            return false;
        }

        static Stream::Builder<T> *builder() {
            return new Stream::Builder<T>();
        }

        static Stream<T> concat(Stream<T> &a, Stream<T> &b) {
            return new Stream<T>();
        }

        int count() {
            return _d.size();
        }

        Stream<T> *distinct() {
            return this;
        }

        static Stream<T> empty() {
            return new Stream();
        }

        Stream<T> *filter(std::function<bool(T &)> f) {
            return this;
        }

        template<typename R>
        Stream<R> *flatMap(std::function<R(T &)> f) {
            return new Stream<R>();
        }

        Stream<double> *flatMapToDouble(std::function<double(T &)> f) {
            return new Stream<double>();
        }

        Stream<int> *flatMapToInt(std::function<int(T &)> f) {
            return new Stream<int>();
        }

        Stream<long> *flatMapToLong(std::function<long(T &)> f) {
            return new Stream<long>();
        }

        void forEach(std::function<void(T &)> f) {

        }

        void forEachOrdered(std::function<void(T &)> f) {

        }

        static Stream<T> *iterate(T &seed, std::function<T &(T &)> f) {
            return Stream<T>();
        }

        Stream<T> *limit(long maxSize) {
            return this;
        }

        template<typename R>
        Stream<R> *map(std::function<R &(T &)> f) {
            return new Stream<R>();
        }

        Stream<double> *mapToDouble(std::function<double(T &)> f) {
            return new Stream<double>();
        }

        Stream<int> *mapToInt(std::function<int(T &)> f) {
            return new Stream<int>();
        }

        Stream<long> *mapToLong(std::function<long(T &)> f) {
            return new Stream<long>();
        }

        bool noneMath(std::function<bool(T &)> f) {
            return false;
        }

        static Stream<T> *of(T &v...) {
            return new Stream<T>();
        }

        static Stream<T> *of(T &v) {
            return new Stream<T>();
        }

        Stream<T> *peek(std::function<void(T &)> f) {
            return this;
        }

        Stream<T> *skip(long n) {
            return new Stream<T>();
        }

        static Stream<T> *make(std::vector<T> &data) {
            return new Stream(data);
        }

    private:
        explicit Stream(std::vector<T> &data) : _d(data) {}

        std::vector<T> &_d;;
    };
}

#endif /* _STREAMPP_H_ */
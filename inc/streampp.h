
#ifndef _STREAMPP_H_
#define _STREAMPP_H_

#include <functional>
#include <valarray>

namespace streampp {

    template<typename T>
    class StreamOperation {
    public:
        enum Status {
            EXEC_FAILED = 0, EXEC_OK = 1, EXEC_NONE = -1
        };

        virtual bool fire(T &node) = 0;
    };


    template<typename T>
    class StreamBoolOperation : public StreamOperation<T> {
    public:
        explicit StreamBoolOperation(std::function<bool(T &)> f) : _f(f) {}

        bool fire(T &node) override {
            return _f(node);
        }

        std::function<bool(T &)> _f;
    };

    template<typename T>
    class StreamVoidOperation : public StreamOperation<T> {
    public:
        explicit StreamVoidOperation(std::function<void(T &)> f) : _f(f) {}

        bool fire(T &node) override {
            _f(node);
            return StreamOperation<T>::Status::EXEC_OK;
        }

        std::function<void(T &)> _f;
    };


    template<typename T, template<class ...> class C>
    class Stream {
    public:

        typedef __gnu_cxx::__normal_iterator<T*, C<T>> StreamIterator;

        ~Stream () {
            std::for_each(_operations.begin(), _operations.end(), [](StreamOperation<T> * op) {
                delete op;
            });
            _operations.clear();
        }

        Stream<T, C> *filter(std::function<bool(T &)> f) {
            _operations.push_back(new StreamBoolOperation<T>(f));
            return this;
        }

        Stream<T, C> *peek(std::function<void(T &)> f) {
            _operations.push_back(new StreamVoidOperation<T>(f));
            return this;
        }

        Stream<T, C> *map(std::function<void(T&)> f) {
            _operations.push_back(new StreamVoidOperation<T>(f));
            return this;
        }

        long count() {
            return std::distance(_c, _e);
        }

        void forEach(std::function<void(T &)> f) {
            _operations.push_back(new StreamVoidOperation<T>(f));
            _consume();
            delete this;
        }

        Stream(StreamIterator begin, StreamIterator end) : _c(begin), _e(end) {}

    private:;

        void _consume() {
            while(_c != _e) {
                for(auto op : _operations) {
                    if(op->fire(*_c) == false) break;
                }
                _c++;
            }
        }

        StreamIterator _c;
        StreamIterator _e;

        std::vector<StreamOperation<T> *> _operations;
    };

    template<typename T>
    class StreamBuilder {
    public:
        static Stream<T, std::vector> *make(std::vector<T> & data) {
            return new Stream<T, std::vector>(data.begin(), data.end());
        }

        static Stream<T, std::set> *make(std::set<T> data){
            return new Stream<T, std::set>(data.begin(), data.end());
        }
    };
}

#endif /* _STREAMPP_H_ */
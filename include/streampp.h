
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
    class StreamCollectOperation : public StreamOperation<T> {
    public:
        virtual C<T> result() = 0;
    };

    template<typename T>
    class StreamVectorCollectOperation : public StreamCollectOperation<T, std::vector> {

    public:
        virtual ~StreamVectorCollectOperation() {
            _container.clear();
        }

        std::vector<T> result() override {
            return _container;
        }

        bool fire(T &node) override {
            _container.push_back(node);
            return StreamOperation<T>::Status::EXEC_OK;
        }

    private:
        std::vector<T> _container;
    };

    template<typename T, template<class ...> class C>
    class Stream {
    public:

        typedef __gnu_cxx::__normal_iterator<T *, C<T>> StreamIterator;

        ~Stream() {
            std::for_each(_operations.begin(), _operations.end(), [](StreamOperation<T> *op) {
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

        Stream<T, C> *map(std::function<void(T &)> f) {
            _operations.push_back(new StreamVoidOperation<T>(f));
            return this;
        }

        Stream<T, C> *limit(long max_size) {
            _end -= std::distance(_current, _end) - max_size;
            return this;
        }

        Stream<T, C> *skip(long skipped) {
            _current += skipped;
            return this;
        }

        long count() {
            long distance = std::distance(_current, _end);
            delete this;
            return distance;
        }

        std::vector<T> collectToVector() {
            auto operation = new StreamVectorCollectOperation<T>();
            _operations.push_back(operation);
            _consume();
            return operation->result();
        }

        void forEach(std::function<void(T &)> f) {
            _operations.push_back(new StreamVoidOperation<T>(f));
            _consume();
            delete this;
        }

        Stream(StreamIterator begin, StreamIterator end) : _current(begin), _end(end) {}

    private:;

        void _consume() {
            while (_current != _end) {
                for (auto op: _operations) {
                    if (op->fire(*_current) == false) break;
                }
                _current++;
            }
        }

        StreamIterator _current;
        StreamIterator _end;

        std::vector<StreamOperation<T> *> _operations;
    };

    template<typename T>
    class StreamBuilder {
    public:
        static Stream<T, std::vector> *make(std::vector<T> &data) {
            return new Stream<T, std::vector>(data.begin(), data.end());
        }

    private:
        StreamBuilder() = default;
    };
}

#endif /* _STREAMPP_H_ */
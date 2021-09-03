
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

    template<typename T>
    class StreamMinComparatorOperation : public StreamOperation<T> {

    public:
        bool fire(T &node) override {
            if(value == nullptr || node < *value)
                value = &node;

            return StreamOperation<T>::EXEC_OK;
        }

        T * min() {
            return value;
        }

    private:
        T * value;
    };

    template<typename T>
    class StreamMaxComparatorOperation : public StreamOperation<T> {

    public:
        bool fire(T &node) override {
            if(value == nullptr || node > *static_cast<const Animal>(value))
                value = &node;

            return StreamOperation<T>::EXEC_OK;
        }

        T * max() {
            return value;
        }

    private:
        T * value;
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
            int size = 0;
            _match(&size);
            delete this;
            return size;
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

        bool allMatch(std::function<bool(T &)> f) {
            _operations.push_back(new StreamBoolOperation<T>(f));
            int size = std::distance(_current, _end);
            int match = 0;
            _match(&match);
            delete this;
            return size == match;
        }

        bool anyMatch(std::function<bool(T &)> f) {
            _operations.push_back(new StreamBoolOperation<T>(f));
            int match = 0;
            _match(&match);
            delete this;
            return match > 0;
        }

        bool noneMatch(std::function<bool(T &)> f) {
            _operations.push_back(new StreamBoolOperation<T>(f));
            int match = 0;
            _match(&match);
            delete this;
            return match == 0;
        }

        T * min() {
            auto * op = new StreamMinComparatorOperation<T>();
            _operations.push_back(op);
            _consume();
            T *min = op->min();
            delete this;
            return min;
        }

        T * max() {
            auto * op = new StreamMaxComparatorOperation<T>();
            _operations.push_back(op);
            _consume();
            T *max = op->max();
            delete this;
            return max;
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

        void _match(int *match_number) {
            while (_current != _end) {
                bool match = true;
                for (auto op: _operations) {
                    if (op->fire(*_current) == false) {
                        match = false;
                        break;
                    }
                }
                *match_number += match ? 1 : 0;
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
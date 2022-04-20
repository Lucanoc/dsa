#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace dsa {
    template <typename T>
    class minHeap {
        public:
        ~minHeap();
        minHeap(minHeap &&) = delete;

        minHeap(const int &);

        template<typename K>
        minHeap(K, K);

        size_t size() const;
        bool empty() const;

        void insert(const T &);
        T extract();

        private:
        void shiftDown(int);
        void shiftUp(int);

        T * root;
        int forbid;
        int tobe;
    };

    template <typename T>
    inline
    minHeap<T>::~minHeap()
    {
        delete [] root;
    }

    template <typename T>
    inline
    minHeap<T>::minHeap(const int & size)
    : root(new T [size + 1]), forbid(size + 1), tobe(1)
    {

    }

    template <typename T>
    template<typename K>
    inline
    minHeap<T>::minHeap(K begin, K end)
    : root(new T [end - begin + 1]), forbid(end - begin + 1), tobe(end - begin + 1)
    {
        for (K i {begin}; i != end; ++i) {
            root[i - begin + 1] = *i;
        }

        for (int i {tobe - 1 / 2}; i != 0; --i) {
            shiftDown(i);
        }
    }

    template <typename T>
    inline
    size_t minHeap<T>::size() const
    {
        return tobe - 1;
    }

    template <typename T>
    inline
    bool minHeap<T>::empty() const
    {
        return size() == 0;
    }

    template <typename T>
    inline
    void minHeap<T>::insert(const T & _t)
    {
        if (tobe == forbid) {
            T * newRoot {new T [forbid + forbid]};

            for (int i {1}; i != forbid; ++i) {
                newRoot[i] = std::move(root[i]);
            }

            delete [] root;

            root = newRoot;
            forbid = forbid + forbid;
        }

        root[tobe++] = _t;

        shiftUp(tobe - 1);
    }

    template <typename T>
    inline
    T minHeap<T>::extract()
    {
        if (empty()) {
            return T();
        }

        T _tmp {std::move(root[1])};

        root[1] = std::move(root[--tobe]);

        shiftDown(1);

        return _tmp;
    }

    template <typename T>
    inline
    void minHeap<T>::shiftDown(int pos)
    {
        T _tmp {std::move(root[pos])};

        while (2 * pos < tobe) {
            int minPos {2 * pos};

            if (minPos + 1 < tobe) {
                if (root[minPos + 1] < root[minPos]) {
                    ++minPos;
                }
            }

            if (root[minPos] <= _tmp) {
                root[pos] = std::move(root[minPos]);

                pos = minPos;
            } else {
                break;
            }
        }

        root[pos] = std::move(_tmp);
    }

    template <typename T>
    inline
    void minHeap<T>::shiftUp(int pos)
    {
        T _tmp {std::move(root[pos])};

        while (pos != 1) {
            if (_tmp < root[pos >> 1]) {
                root[pos] = std::move(root[pos >> 1]);

                pos >>= 1;
            } else {
                break;
            }
        }

        root[pos] = std::move(_tmp);
    }
}
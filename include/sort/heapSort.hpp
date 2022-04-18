#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class minHeap {
    public:
    ~minHeap()
    {
        delete [] heap;
    }

    minHeap(minHeap && m)
    : heap(m.heap) {m.heap = nullptr;}
    minHeap & operator=(minHeap && m)
    {
        delete [] heap;

        heap = m.heap;
        m.heap =nullptr;
    }

    minHeap(const int & reserve)
    : heap(new T [reserve + 1]), to(1), forbid(reserve + 1)
    {

    }

    template <typename It>
    minHeap(It begin, It end)
    : heap(new T [end - begin + 1]), forbid(end - begin + 1), to(end - begin + 1)
    {
        for (It i = begin; i != end; ++i) {
            heap[i - begin + 1] = *i;
        }

        for (int i = (to - 1) / 2; i != 0; --i) {
            shiftDown(i);
        }
    }

    int size() const;
    bool empty() const;

    void insert(const T & );
    T extract();

    private:
    void shiftUp(int);
    void shiftDown(int);

    T * heap;
    int forbid;
    int to; 
};

template <typename T>
inline
int minHeap<T>::size() const
{
    return to - 1;
}

template <typename T>
inline
bool minHeap<T>::empty() const
{
    return size() == 0;
}

template <typename T>
void minHeap<T>::insert(const T & data)
{
    if (to == forbid) {
        T * _newHeap = new T [forbid + forbid];

        for (int i = 1; i != forbid; ++i) {
            _newHeap[i] = std::move(heap[i]);
        }

        delete [] heap;
        heap = _newHeap;

        forbid = forbid + forbid;
    }

    heap[to++] = data;

    shiftUp(to - 1);
}

template <typename T>
T minHeap<T>::extract()
{
    if (empty()) {
        throw std::out_of_range("no items in heap/n");
    }

    T _tmp = std::move(heap[1]);

    heap[1] = std::move(heap[--to]);

    shiftDown(1);

    return _tmp;
}

template <typename T>
inline
void minHeap<T>::shiftDown(int key)
{
    T _tmp = std::move(heap[key]);

    while (key * 2 <  to) {
        int minPos = key * 2;

        if (minPos + 1 < to) {
            if (heap[minPos + 1] < heap[minPos]) {
                ++minPos;
            }
        }

        if (_tmp > heap[minPos]) {
            heap[key] = std::move(heap[minPos]);

            key = minPos;
        } else {
            break;
        }
    }

    heap[key] = std::move(_tmp);
}

template <typename T>
inline
void minHeap<T>::shiftUp(int key)
{
    T _tmp = std::move(heap[key]);

    while (key != 1) {
        if (_tmp < heap[key >> 1]) {
            heap[key] = std::move(heap[key >> 1]);

            key  = key >> 1;
        } else {
            break;
        }
    }

    heap[key] = std::move(_tmp);
}
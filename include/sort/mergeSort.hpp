#pragma once

#include "sort/insertionSort.hpp"
#include <iterator>

namespace dsa {
    template <typename T>
    inline
    void __mergeSort(T begin, T end)
    {
        typename std::iterator_traits<T>::value_type _local[end - begin];

        for (T i {begin}; i != end; ++i) {
            _local[i - begin] = std::move(*i);
        }

        long lbegin {0}, mid {(end - begin) >> 1}, rbegin {mid};

        for (T i {begin}; i != end; ++i) {
            if (lbegin == mid) {
                *i = std::move(_local[rbegin++]);

                continue;
            }
            
            if (rbegin == end - begin) {
                *i = std::move(_local[lbegin++]);

                continue;
            }

            if (_local[lbegin] < _local[rbegin]) {
                *i = std::move(_local[lbegin++]);
            } else {
                *i = std::move(_local[rbegin++]);
            }
        }
    }

    template <typename T>
    inline
    void mergeSort(T begin, T end)
    {
        if (end - begin <= 1) {
            insertionSort(begin, end);

            return;
        }

        T mid {((end - begin) >> 1) + begin};

        mergeSort(begin, mid);
        mergeSort(mid, end);

        if (*mid < *(mid - 1)) {
            __mergeSort(begin, end);
        }
    }
}
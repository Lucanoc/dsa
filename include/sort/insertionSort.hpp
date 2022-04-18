#pragma once

#include <iterator>

namespace dsa {
    template <typename T>
    inline
    void insertionSort(T begin, T end)
    {
        if (end - begin <= 1) {
            return;
        }

        for (T i {begin}; i != end; ++i) {
            typename std::iterator_traits<T>::value_type _tmp {std::move(*i)};

            T pos {i};

            for (; pos != begin; --pos) {
                if (_tmp < *(pos - 1)) {
                    *pos = std::move(*(pos - 1));
                } else {
                    break;
                }
            }

            *pos = std::move(_tmp);
        }
    }
}
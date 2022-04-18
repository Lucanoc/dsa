#pragma once

#include <algorithm>

namespace dsa {
    template <typename T>
    inline
    void selectionSort(T begin, T end)
    {
        if (end - begin <= 1) {
            return;
        }

        for (T i {begin}; i != end; ++i) {
            T minPos {i};

            for (T j {i + 1}; j != end; ++j) {
                if (*j < *minPos) {
                    minPos = j;
                }
            }

            std::swap(*i, *minPos);
        }
    }
}
#pragma once

#include "sort/insertionSort.hpp"
#include <random>
#include <ctime>
namespace dsa {
    template <typename T>
    inline
    T __quickSort(T begin, T end)
    {
        std::default_random_engine e(time(nullptr));

        std::uniform_int_distribution<int> d(0, end - begin - 1);

        std::swap(*begin, *(begin + d(e)));

        T last {begin};

        for (T i {begin + 1}; i != end; ++i) {
            if (*i < *begin) {
                std::swap(*(++last), *i);
            }
        }

        std::swap(*last, *begin);

        return last;
    }

    template <typename T>
    inline
    void quickSort(T begin, T end)
    {
        if (end - begin <= 1) {
            insertionSort(begin, end);

            return;
        }

        T base {__quickSort(begin, end)};

        quickSort(begin, base);
        quickSort(base + 1, end);
    }

    template <typename T>
    struct lasts {
        T llast {};
        T rlast {};
    };

    template <typename T>
    inline
    lasts<T> __quickSort3(T begin, T end)
    {
        std::default_random_engine e(time(nullptr));

        std::uniform_int_distribution<int> d(0, end - begin - 1);

        std::swap(*begin, *(begin + d(e)));

        lasts<T> l {begin, end};

        T moving {begin + 1};

        while (moving != l.rlast) {
            if (*moving < *begin) {
                std::swap(*moving, *(++l.llast));
            } else if (*begin < *moving) {
                std::swap(*moving, *(--l.rlast));

                continue;
            }

            ++moving;
        }

        std::swap(*begin, *l.llast);

        return l;
    }

    template <typename T>
    inline
    void quickSort3(T begin, T end)
    {
        if (end - begin <= 1) {
            insertionSort(begin, end);

            return;
        }

        auto [llast, rlast] {__quickSort3(begin, end)};

        quickSort3(begin, llast);
        quickSort3(rlast, end);
    }
}
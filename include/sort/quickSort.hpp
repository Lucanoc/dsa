#pragma once

#include "sort/insertionSort.hpp"
#include <iostream>
#include <random>
#include <ctime>

template <typename T>
T __quickSort(T begin, T end)
{
    std::default_random_engine e(std::time(nullptr));
    
    std::uniform_int_distribution<int> d(0, end - begin - 1);

    std::swap(*begin, *(begin + d(e)));

    T right = begin;

    for (T i = begin + 1; i != end; ++i) {
        if (*i < *begin) {
            std::swap(*i, *(++right));
        }
    }

    std::swap(*begin, *right);

    return right;
}

template <typename T>
void quickSort(T begin, T end)
{
    if (end - begin <= 1) {
        insertionSort(begin, end);

        return;
    }

    T _base = __quickSort(begin, end);

    quickSort(begin, _base);
    quickSort(_base + 1, end);
}

template <typename T>
struct itSaver {
    T left;
    T right;
};

template <typename T>
itSaver<T> __quickSort2(T begin, T end)
{
    std::cout << __FUNCTION__ << '\n';

    std::default_random_engine e(std::time(nullptr));

    std::uniform_int_distribution<int> d(0, end - begin - 1);

    std::swap(*begin, *(begin + d(e)));

    // srand(time(nullptr));
    // std::swap(*begin, *(rand() % (end - begin) + begin));

    itSaver<T> saver {begin, end};

    T mover = begin + 1;

    while (mover != saver.right) {
        if (*mover < *begin) {
            std::swap(*mover, *(++saver.left));

            ++mover;
        } else if (*mover > *begin) {
            std::swap(*mover, *(--saver.right));
        } else {
            ++mover;
        }
    }

    std::swap(*begin, *saver.left);

    return saver;
}

template <typename T>
void quickSort2(T begin, T end)
{
    if (end - begin <= 1) {
        insertionSort(begin, end);

        return;
    } 

    auto [left, right] = __quickSort2(begin, end);

    quickSort2(begin, left);
    quickSort2(right, end);
}
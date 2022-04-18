#pragma once

template <typename T, typename V>
inline
T binarySearch(T begin, T end, const V & des)
{
    T res = begin;

    while (begin != end) {
        T mid = ((end - begin) >> 1) + begin;

        if (*mid < des) {
            begin = mid + 1;
        } else if (*mid > des) {
            end = mid;
        } else {
            res = mid;

            break;
        }
    }

    return res;
}
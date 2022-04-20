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

namespace dsa {
    template <typename T, typename K>
    T binarySearch(T begin, T end, const K & des)
    {
        if (end - begin <= 0) {
            return T();
        }

        while (begin != end) {
            T mid {((end - begin) >> 1) + begin};

            if (*mid < des) {
                begin = mid + 1;
            } else if (des < *mid) {
                end = mid;
            } else {
                return mid;
            }
        }

        return T();
    }
}
#pragma once
#include <cstddef>
#include <functional>

namespace myHash {
    template <typename T>
    inline
    void hash_combile(std::size_t & res, const T & ct)
    {
        res ^= std::hash<T>()(ct) + 0x9e3779b9 + (res << 6) + (res >> 2);
    }

    template <typename T>
    inline
    void hash_val(std::size_t & res, const T & ct)
    {
        hash_combile(res, ct);
    }

    template <typename T, typename ... Ts>
    inline
    void hash_val(std::size_t & res, const T & ct, const Ts & ... cts)
    {
        hash_combile(res, ct);

        hash_val(res, cts...);
    }

    template <typename ... Ts>
    inline
    size_t hash_val(const Ts & ... cts)
    {
        size_t res {};

        hash_val(res, cts...);

        return res;
    }
}
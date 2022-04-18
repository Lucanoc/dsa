#pragma once

#include <ostream>
#include <tuple>

template <int IDX, int MAX, typename ... Ts>
struct PRINT_TUPLE {
    static void print(std::ostream & os, const std::tuple<Ts...> & tp)
    {
        os << std::get<IDX>(tp) << (IDX + 1 == MAX ? "" : ", ");

        PRINT_TUPLE<IDX + 1, MAX, Ts...>::print(os, tp);
    }
};

template <int MAX, typename ... Ts>
struct PRINT_TUPLE<MAX, MAX, Ts...> {
    static void print(std::ostream & os, const std::tuple<Ts...> & tp)
    {
        return;
    }
};

template <typename ... Ts>
std::ostream & operator<<(std::ostream & os, const std::tuple<Ts...> & tp)
{
    os << '[';

    PRINT_TUPLE<0, sizeof...(Ts), Ts...>::print(os, tp);

    return os << ']';
}
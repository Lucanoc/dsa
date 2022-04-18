#pragma once

#include "gragh/gragh.hpp"
#include <utility>

template <typename GRAGH>
class dfs {
    public:
    ~dfs();
    dfs(const dfs &) = delete;

    dfs(GRAGH &);

    template<typename FUNC>
    void operator()(const int &, FUNC &&);

    private:
    template<typename FUNC>
    void __dfs(const int &, FUNC &&);

    GRAGH & g;
    bool * visited;
};

template <typename T>
inline
dfs<T>::~dfs()
{
    delete [] visited;
}

template <typename T>
inline
dfs<T>::dfs(T & _g)
: g(_g), visited(new bool [_g.sizeofNodes()])
{
    
}

template <typename G>
template<typename FUNC>
inline
void dfs<G>::operator()(const int & start, FUNC && func)
{
    if (start < 0 || start >= g.sizeofNodes()) {
        return;
    }

    for (int i = 0; i != g.sizeofNodes(); ++i) {
        visited[i] = false;
    }

    __dfs(start, std::forward<FUNC>(func));
}

template <typename G>
template<typename FUNC>
inline
void dfs<G>::__dfs(const int & nowNode, FUNC && func)
{
    visited[nowNode] = true;

    func(nowNode);

    for (const graghNode<typename G::value_type> & i : g.getEdges(nowNode)) {
        if (i.to != -1) {
            if (!visited[i.to]) {
                __dfs(i.to, std::forward<FUNC>(func));
            }
        }
    }
}
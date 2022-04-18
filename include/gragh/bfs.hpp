#pragma once

#include "gragh.hpp"
#include <deque>

template <typename GRAGH>
class bfs {
    public:
    ~bfs()
    {
        delete [] visited;
        delete [] parents;
    }

    bfs(GRAGH & _g)
    : g(_g), visited(new bool [_g.sizeofNodes()]), parents(new int [_g.sizeofNodes()])
    {

    }

    template <typename FUNC>
    const int * operator()(const int & start, FUNC && func)
    {
        if (start < 0 || start >= g.sizeofNodes()) {
            return nullptr;
        }

        std::deque<int> d;

        for (int i = 0; i != g.sizeofNodes(); ++i) {
            visited[i] = false;
            parents[i] = 0;
        }

        d.push_back(start);
        visited[start] = true;

        while (!d.empty()) {
            for (const graghNode<typename GRAGH::value_type> & i : g.getEdges(d.front())) {
                if (i.to != -1) {
                    if (!visited[i.to]) {
                        d.push_back(i.to);
                        visited[i.to] = true;
                        parents[i.to] = parents[d.front()] + 1;
                    }
                }
            }

            func(d.front());

            d.pop_front();
        }

        return parents;
    }

    private:
    GRAGH & g;
    bool * visited;
    int * parents;
};
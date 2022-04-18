#pragma once

#include <vector>
#include "gragh/gragh.hpp"
#include "sort/heapSort.hpp"
#include "unionFind.hpp"

template <typename G>
class mst {
    public:
    mst(G & _g)
    : g(_g)
    {
        minHeap<graghNode<typename G::value_type>> mh(g.sizeofEdges());

        for (int i = 0; i != g.sizeofNodes(); ++i) {
            for (const graghNode<typename G::value_type> & i : g.getEdges(i)) {
                if (i.from != -1) {
                    if (i.from < i.to) {
                        mh.insert(i);
                    }
                }
            }
        }

        unionFind uf(g.sizeofNodes());

        while (!mh.empty()) {
            graghNode<typename G::value_type> _tmp(mh.extract());

            if (!uf.isConnected(_tmp.from, _tmp.to)) {
                res.push_back(std::move(_tmp));

                uf.toUnion(res.back().from, res.back().to);
            }
        }
    }

    const std::vector<graghNode<typename G::value_type>> & getMst() const
    {
        return res;
    }

    private:
    G & g;
    std::vector<graghNode<typename G::value_type>> res;
};
#pragma once

#include <vector>
template <typename T>
struct graghNode {
    graghNode(const int & _from = -1, const int & _to = -1, const T & _cost = T())
    : from(_from), to(_to), cost(_cost)
    {

    }

    bool operator<(const graghNode & _g)
    {
        return cost < _g.cost;
    }

    bool operator>(const graghNode & _g)
    {
        return cost > _g.cost;
    }

    int from = -1;
    int to = -1;
    T cost;
};

template <typename T>
class gragh {
    public:
    typedef T value_type;

    gragh(const int &, const bool & = false);

    void setEdge(const int &, const int &, const T &);
    const std::vector<graghNode<T>> & getEdges(const int &) const;

    int sizeofEdges() const;
    int sizeofNodes() const;

    private:
    std::vector<std::vector<graghNode<T>>> g;
    bool hasDirection;
};

template <typename T>
inline
gragh<T>::gragh(const int & _cnt, const bool & _hasDirection)
: g(_cnt, std::vector<graghNode<T>>(_cnt, graghNode<T>(-1, -1, T()))), hasDirection(_hasDirection)
{

}

template <typename T>
inline
void gragh<T>::setEdge(const int & node1, const int & node2, const T & cost)
{
    if (node1 < 0 || node1 >= g.size() || node2 < 0 || node2 >= g.size()) {
        return;
    }

    g[node1][node2].from = node1;
    g[node1][node2].to = node2;
    g[node1][node2].cost = cost;

    if (!hasDirection) {
        g[node2][node1].from = node2;
        g[node2][node1].to = node1;
        g[node2][node1].cost = cost;
    }
}

template <typename T>
inline
const std::vector<graghNode<T>> & gragh<T>::getEdges(const int & node) const
{
    if (node < 0 || node >= g.size()) {
        return std::vector<graghNode<T>>();
    }

    return g[node];
}

template <typename T>
inline
int gragh<T>::sizeofEdges() const
{
    int cnt = 0;

    for (const std::vector<graghNode<T>> & i : g) {
        for (const graghNode<T> & j : i) {
            if (j.from != -1) {
                ++cnt;
            }
        }
    }

    return cnt;
}

template <typename T>
inline
int gragh<T>::sizeofNodes() const
{
    return g.size();
}
#pragma once

class unionFind {
    public:
    ~unionFind();
    unionFind(unionFind &&);
    unionFind & operator=(unionFind &&);

    explicit unionFind(const int &);

    bool isConnected(const int &, const int &) const;
    void toUnion(const int &, const int &);

    private:
    int find(const int &) const;

    int * parents;
    int * rank;
    int maxSize;
};

inline
unionFind::~unionFind()
{
    delete [] parents;
    delete [] rank;
}

inline
unionFind::unionFind(unionFind && ru)
: parents(nullptr), rank(nullptr)
{
    parents = ru.parents;
    rank = ru.rank;
    maxSize = ru.maxSize;

    ru.parents = nullptr;
    ru.rank = nullptr;
    ru.maxSize = 0;
}

inline
unionFind & unionFind::operator=(unionFind && ru)
{
    if (&ru != this) {
        delete [] parents;
        delete [] rank;

        parents = ru.parents;
        rank = ru.rank;
        maxSize = ru.maxSize;

        ru.parents = nullptr;
        ru.rank = nullptr;
        ru.maxSize = 0;
    }

    return *this;
}

inline
unionFind::unionFind(const int & size)
: parents(new int [size]), rank(new int [size]), maxSize(size)
{
    for (int i = 0; i != maxSize; ++i) {
        parents[i] = i;
        rank[i] = 1;
    }
}

inline
bool unionFind::isConnected(const int & node1, const int & node2) const
{
    int root1 = find(node1);
    int root2 = find(node2);

    if (root2 == root1) {
        return true;
    } else {
        return false;
    }
}

inline
void unionFind::toUnion(const int & node1, const int & node2)
{
    int root1 = find(node1);
    int root2 = find(node2);

    if (root2 == root1) {
        return;
    }

    if (rank[root1] < rank[root2]) {
        parents[root1] = root2;
    } else if (rank[root2] < rank[root1]) {
        parents[root2] = root1;
    } else {
        parents[root1] = root2;

        ++rank[root2];
    }
}

inline
int unionFind::find(const int & node) const
{
    if (node < 0 || node >= maxSize) {
        return -1;
    }

    int res = node;

    while (parents[res] != res) {
        res = parents[res];
    }

    return res;
}
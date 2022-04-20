#pragma once

#include <stdexcept>
namespace dsa {
    template <typename K, typename V>
    struct treeNode {
        K key {};
        V value {};
        treeNode * left {};
        treeNode * right {};
    };

    template <typename K, typename V>
    void treeReverse(treeNode<K, V> * nowNode)
    {
        while (nowNode) {
            treeNode<K, V> * _tmp {nowNode->left};
            nowNode->left = nowNode->right;
            nowNode->right = _tmp;

            treeReverse(nowNode->left);
            treeReverse(nowNode->right);
        }
    }

    template <typename K, typename V>
    class bst {
        public:
        ~bst();
        bst(bst &&) = delete;

        bst();

        void insert(const K &, const V &);
        void remove(const K &);
        bool contain(const K &) const;
        const V & operator[](const K &) const;

        private:
        void destory(treeNode<K, V> *);
        treeNode<K, V> * inserting(treeNode<K, V> *, const K &, const V &);
        treeNode<K, V> * removing(treeNode<K, V> *, const K &);
        treeNode<K, V> * finding(treeNode<K, V> *, const K &) const;
        treeNode<K, V> * getMaxNode(treeNode<K, V> *);
        treeNode<K, V> * getMinNode(treeNode<K, V> *);

        treeNode<K, V> * root;
    };

    template <typename K, typename V>
    inline
    bst<K, V>::~bst()
    {
        if (root) {
            destory(root);
        }
    }

    template <typename K, typename V>
    inline
    bst<K, V>::bst()
    : root(nullptr)
    {

    }

    template <typename K, typename V>
    inline
    void bst<K, V>::insert(const K & key, const V & value)
    {
        root = inserting(root, key, value);
    }

    template <typename K, typename V>
    inline
    void bst<K, V>::remove(const K & key)
    {
        if (contain(key)) {
            removing(root, key);
        }
    }

    template <typename K, typename V>
    inline
    bool bst<K, V>::contain(const K & key) const
    {
        if (finding(root, key)) {
            return true;
        } else {
            return false;
        }
    }

    template <typename K, typename V>
    inline
    const V & bst<K, V>::operator[](const K & key) const
    {
        treeNode<K, V> * res {finding(root, key)};

        if (res) {
            return res->value;
        } else {
            throw std::logic_error("no key in tree\n");
        }
    }

    template <typename K, typename V>
    inline
    treeNode<K, V> * bst<K, V>::inserting(treeNode<K, V> * nowNode, const K & key, const V & value) {
        if (nowNode) {
            if (key < nowNode->key) {
                nowNode->left = inserting(nowNode->left, key, value);
            } else if (nowNode->key < key) {
                nowNode->right = inserting(nowNode->right, key, value);
            } else {
                nowNode->value = value;
            }

            return nowNode;
        } else {
            return new treeNode<K, V> {key, value};
        }
    }

    template <typename K, typename V>
    inline
    treeNode<K, V> * bst<K, V>::removing(treeNode<K, V> * nowNode, const K & key)
    {
        if (nowNode->key < key) {
            nowNode->right = removing(nowNode->right, key);
        } else if (key < nowNode->key) {
            nowNode->left = removing(nowNode->left, key);
        } else {
            if (!nowNode->left) {
                treeNode<K, V> * _tmp {nowNode->right};
                delete nowNode;

                return _tmp;
            }

            if (!nowNode->right) {
                treeNode<K, V> * _tmp {nowNode->left};

                delete nowNode;

                return _tmp;
            }

            auto [_key, _value, _left, _right] {*getMaxNode(nowNode->left)};

            nowNode->left = removing(nowNode->left, _key);

            nowNode->key = _key;
            nowNode->value = _value;
        }

        return nowNode;
    }

    template <typename K, typename V>
    inline
    treeNode<K, V> * bst<K, V>::finding(treeNode<K, V> * nowNode, const K & key) const
    {
        if (nowNode) {
            if (key < nowNode->key) {
                return finding(nowNode->left, key);
            } else if (nowNode->key < key) {
                return finding(nowNode->right, key);
            } else {
                return nowNode;
            }
        } else {
            return nullptr;
        }
    }

    template <typename K, typename V>
    inline
    treeNode<K, V> * bst<K, V>::getMaxNode(treeNode<K, V> * nowNode)
    {
        if (nowNode) {
            if(nowNode->right) {
                return getMaxNode(nowNode->right);
            } else {
                return nowNode;
            }
        } else {
            return nullptr;
        }
    }

    template <typename K, typename V>
    inline

    treeNode<K, V> * bst<K, V>::getMinNode(treeNode<K, V> * nowNode)
    {
        if (nowNode) {
            if (nowNode->left) {
                return getMinNode(nowNode->left);
            } else {
                return nowNode;
            }
        } else {
            return nullptr;
        }
    }

    template <typename K, typename V>
    inline
    void bst<K, V>::destory(treeNode<K, V> * nowNode)
    {
        if(nowNode) {
            destory(nowNode->left);
            destory(nowNode->right);

            delete nowNode;
        }
    }
}
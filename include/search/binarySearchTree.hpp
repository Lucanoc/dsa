#pragma once

#include <stdexcept>
template <typename K, typename V>
struct treeNode {
    K key;
    V value;
    treeNode * left = nullptr;
    treeNode * right = nullptr;
};

template <typename K, typename V>
inline
void treeReverse(treeNode<K, V> * nowNode)
{
    if (nowNode) {
        treeNode<K, V> * _tmp = nowNode->left;
        nowNode->left = nowNode->right;
        nowNode->right = _tmp;

        treeReverse(nowNode->left);
        treeReverse(nowNode->right);
    }
}

template <typename K, typename V>
class binarySearchTree {
    public:
    ~binarySearchTree()
    {
        if (root) {
            __destory(root);
        }
    }

    binarySearchTree(binarySearchTree &&);
    binarySearchTree & operator=(binarySearchTree &&);

    binarySearchTree()
    : root(nullptr)
    {

    }

    void setKey(const K &, const V &);
    void deleteKey(const K &);
    bool contain(const K &) const;
    const V & operator[](const K &) const;

    private:
    treeNode<K, V> * __setKey(treeNode<K, V> *, const K &, const V &);
    treeNode<K, V> * __deleteKey(treeNode<K, V> *, const K &);
    treeNode<K, V> * __contain(treeNode<K, V> *, const K &) const;
    treeNode<K, V> * __get(treeNode<K, V> *, const K &) const;
    treeNode<K, V> * __getMaxKey(treeNode<K, V> *);
    treeNode<K, V> * __getMinKey(treeNode<K, V> *);

    void __destory(treeNode<K, V> *);

    treeNode<K, V> * root;
};

template <typename K, typename V>
inline
void binarySearchTree<K, V>::__destory(treeNode<K, V> * nowNode)
{
    if (nowNode) {
        __destory(nowNode->left);
        __destory(nowNode->right);

        delete nowNode;
    }
}

template <typename K, typename V>
inline
void binarySearchTree<K, V>::setKey(const K & key, const V & value)
{
    root = __setKey(root, key, value);
}

template <typename K, typename V>
inline
void binarySearchTree<K, V>::deleteKey(const K & key)
{
    if (contain(key)) {
        root = __deleteKey(root, key);
    }
}

template <typename K, typename V>
inline
bool binarySearchTree<K, V>::contain(const K & key) const
{
    if (__contain(root, key)) {
        return true;
    } else {
        return false;
    }
}

template <typename K, typename V>
inline
const V & binarySearchTree<K, V>::operator[](const K & key) const
{
    if (contain(key)) {
        return __get(root, key)->value;
    } else {
        throw std::out_of_range("no this key in mst\n");
    }
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__setKey(treeNode<K, V> * nowNode, const K & key, const V & value)
{
    if (nowNode) {
        if (nowNode->key == key) {
            nowNode->value = value;
        } else if (nowNode->key < key) {
            nowNode->right = __setKey(nowNode->right, key, value);
        } else {
            nowNode->left = __setKey(nowNode->left, key, value);
        }

        return nowNode;
    } else {
        return new treeNode<K, V> {key, value};
    }
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__deleteKey(treeNode<K, V> * nowNode, const K & key)
{
    if (nowNode->key < key) {
        nowNode->right = __deleteKey(nowNode->right, key);
    } else if (nowNode->key > key) {
        nowNode->left = __deleteKey(nowNode->left, key);
    } else {
        if (!nowNode->left) {
            treeNode<K, V> * _tmp = nowNode->right;

            delete nowNode;

            return _tmp;
        }

        if (!nowNode->right) {
            treeNode<K, V> * _tmp = nowNode->left;

            delete nowNode;

            return _tmp;
        }

        auto [_key, _value, _left, _right] 
        = *__getMaxKey(nowNode->left);

        deleteKey(_key);

        nowNode->key = _key;
        nowNode->value = _value;
    }

    return nowNode;
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__contain(treeNode<K, V> * nowNode, const K & key) const 
{
    if (nowNode) {
        if (nowNode->key == key) {
            return nowNode;
        } else if (nowNode->key < key) {
            return __contain(nowNode->right, key);
        } else {
            return __contain(nowNode->left, key);
        }
    } else {
        return nullptr;
    }
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__get(treeNode<K, V> * nowNode, const K & key) const
{
    if (nowNode->key < key) {
        return __get(nowNode->right, key);
    } else if (nowNode->key > key) {
        return __get(nowNode->left, key);
    } else {
        return nowNode;
    }
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__getMaxKey(treeNode<K, V> * nowNode)
{
    if (nowNode) {
        if (nowNode->right) {
            return __getMaxKey(nowNode->right);
        } else {
            return nowNode;
        }
    } else {
        return nullptr;
    }
}

template <typename K, typename V>
inline
treeNode<K, V> * binarySearchTree<K, V>::__getMinKey(treeNode<K, V> * nowNode)
{
    if (nowNode) {
        if (nowNode->left) {
            return __getMinKey(nowNode->left);
        } else {
            return nowNode;
        }
    } else {
        return nullptr;
    }
}
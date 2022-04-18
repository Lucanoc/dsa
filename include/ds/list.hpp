#pragma once

#include <cstddef>

template <typename T>
struct listNode {
    explicit listNode(const T & _data = T())
    : data(_data)
    {

    }

    T data;
    listNode * next = nullptr;
};

template <typename T>
class myList {
    public:
    ~myList();
    myList(myList &&) noexcept;
    myList & operator=(myList &&) noexcept;

    myList();

    int size() const;

    void insert(const T &);
    void insert(const T &, const int &);
    void remove();
    void remove(const int &);

    void setValue(const T &, const int &);
    const T & getValue(const int &) const;

    void reverse(const int &, const int &);

    private:
    void locate(const int & index) const
    {
        before = root;

        if (index <= 0) {
            before = nullptr;
        }

        for (int i = 1; i != index; ++i) {
            before = before->next;

            if (!before) {
                break;
            }
        }
    }

    listNode<T> * reversing(listNode<T> *, listNode<T> *);

    listNode<T> * root;
    listNode<T> * far;
    mutable listNode<T> * before;
};

template <typename T>
inline
myList<T>::~myList()
{
    while (root) {
        listNode<T> * _tmp = root;

        root = root->next;

        delete _tmp;
    }
}

template <typename T>
inline
myList<T>::myList()
: root(new listNode<T>())
{
    far = root;
    before = root;
}

template <typename T>
inline
int myList<T>::size() const
{
    if (root == far) {
        return 0;
    }

    int res = 0;

    listNode<T> * nowNode = root->next;

    while (nowNode) {
        ++res;

        nowNode = nowNode->next;
    }

    return res;
}

template <typename T>
inline
void myList<T>::insert(const T & _t)
{
    far->next = new listNode<T>(_t);

    far = far->next;
}

template <typename T>
inline
void myList<T>::insert(const T & _t, const int & _pos)
{
    locate(_pos);

    if (!before) {
        return;
    }

    listNode<T> * _tmp = new listNode<T>(_t);

    _tmp->next = before->next;

    before->next = _tmp;
}

template <typename T>
inline
void myList<T>::remove()
{
    remove(size());
}

template <typename T>
inline
void myList<T>::remove(const int & _pos)
{
    locate(_pos);

    if (before->next == far) {
        far = before;
    }

    listNode<T> * _tmp = before->next->next;

    delete before->next;

    before->next = _tmp;
}

template <typename T>
void myList<T>::reverse(const int & _from, const int & _to)
{
    locate(_from);

    if (!before) {
        return;
    }

    listNode<T> * front = before;
    listNode<T> * from = before->next;

    locate(_to);

    if (!before) {
        return;
    }

    listNode<T> * to = before->next;
    listNode<T> * back = to->next;

    reversing(from, to)->next = back;
    front->next = to;
}

template <typename T>
inline
listNode<T> * myList<T>::reversing(listNode<T> * from, listNode<T> * to)
{
    if (from != to) {
        reversing(from->next, to)->next = from;
    }

    return from;
}

template <typename T>
inline
const T & myList<T>::getValue(const int & _pos) const
{
    locate(_pos);

    if (!before) {
        return T();
    }

    return before->next->data;
}
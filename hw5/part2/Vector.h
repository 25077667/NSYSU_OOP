#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <iostream>
#include "Trace.h"
using std::cout;
using std::endl;

static int counter = 1;

template <class T>
class vector
{
    T *v;
    int sz;

public:
    vector()
    {
        TRACE(dummy, "vector<T>::vector(int)");
        v = nullptr;
        sz = -1;
        cout << "  count = " << counter << endl;
    }
    vector(int size)
    {
        TRACE(dummy, "vector<T>::vector(int)");
        v = new T[size];
        sz = size;
        cout << "  count = " << counter << endl;
    }
    ~vector()
    {
        TRACE(dummy, "vector<T>::~vector");
        delete[] v;
        v = nullptr;
        sz = -1;
        cout << "  count = " << counter << endl;
    }

    T &elem(int i) { return v[i]; }
    T &operator[](int i) { return v[i]; }
};

template <>
class vector<void *>
{
    void **v;
    int sz;

public:
    vector()
    {
        TRACE(dummy, "vector<void*>::vector(int)");
        v = nullptr;
        sz = -1;
        cout << "  count = " << counter++ << endl;
    }
    explicit vector(int i)
    {
        TRACE(dummy, "vector<void*>::vector(int)");
        v = new void *[i];
        sz = i;
        cout << "  count = " << counter++ << endl;
    }
    ~vector()
    {
        TRACE(dummy, "vector<void*>::~vector");
        delete[] v;
        v = nullptr;
        sz = -1;
        cout << "  count = " << --counter << endl;
    }

    void *&elem(int i) { return static_cast<void *&>(v[i]); }
    void *&operator[](int i) { return static_cast<void *&>(v[i]); }
};

template <class T>
class vector<T *> : private vector<void *>
{
    T **v;
    int sz;

public:
    vector()
    {
        TRACE(dummy, "vector<T*>::vector(int)");
        v = nullptr;
        sz = -1;
    }
    explicit vector(int i)
    {
        TRACE(dummy, "vector<T*>::vector(int)");
        v = new T *[i];
        sz = i;
    }
    ~vector()
    {
        TRACE(dummy, "vector<T*>::~vector");
        delete[] v;
        v = nullptr;
        sz = -1;
    }

    T *&elem(int i) { return static_cast<T *&>(v[i]); }
    T *&operator[](int i) { return static_cast<T *&>(v[i]); }
};

#endif

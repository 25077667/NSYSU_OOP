#ifndef __VECTOR_H__
#define __VECTOR_H__

template <class T>
class vector
{
    T *v;
    int sz;

public:
    vector()
    {
        v = nullptr;
        sz = -1;
    }
    vector(int size)
    {
        v = new T[size];
        sz = size;
    }
    ~vector()
    {
        delete[] v;
        v = nullptr;
        sz = -1;
    }

    T &elem(int i) { return v[i]; }
    T &operator[](int i) { return v[i]; }
};

#endif

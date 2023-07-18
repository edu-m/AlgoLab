#pragma once
#include <iostream>

using namespace std;

template <class H>
class BHeap
{
public:
    virtual void heapify(int index) = 0;
    virtual bool enqueue(H x) = 0;
    virtual H *top() = 0;
    virtual H *extract() = 0;
    virtual void buildHeap() = 0;
    virtual void print() = 0;
};
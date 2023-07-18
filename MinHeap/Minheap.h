#pragma once
#include <iostream>
#include "BHeap.h"

using namespace std;

template <class H>
class MinHeap : public BHeap<H>
{
    int heapsize;
    int queueLength;
    H **queue;

public:
    MinHeap()
    {
    }
    MinHeap(H **array, int size, int arrayLength)
    {
        queueLength = arrayLength - 1;
        heapsize = size - 1;
        this->queue = array;
        buildHeap();
    }
    int getParent(int i)
    {
        return i / 2;
    }
    int getLeft(int i)
    {
        return i * 2;
    }
    int getRight(int i)
    {
        return i * 2 + 1;
    }
    void swap(int a, int b)
    {
        H *temp = queue[a];
        queue[a] = queue[b];
        queue[b] = temp;
    }
    bool enqueue(H x)
    {
        if (queueLength == heapsize)
            return false;
        *queue[++queueLength] = x;
        int i = queueLength;
        while (i > 1 && *queue[i] < *queue[getParent(i)])
        {
            swap(i, getParent(i));
            i = getParent(i);
        }
        return true;
    }
    H *top()
    {
        if (queueLength == 0)
            return NULL;
        return queue[1];
    }
    H *extract()
    {
        if (queueLength == 0)
            return NULL;
        swap(1, queueLength--);
        heapify(1);
        return queue[queueLength + 1];
    }

    void heapify(int index)
    {
        int i = index;
        while (i <= queueLength / 2)
        {
            int min = i;
            int l = getLeft(i);
            int r = getRight(i);
            if (l <= queueLength && *queue[l] < *queue[min])
                min = l;
            if (r <= queueLength && *queue[r] < *queue[min])
                min = r;
            if (min == i)
                break;
            swap(min, i);
            i = min;
        }
    }
    void buildHeap()
    {
        for (int i = heapsize / 2; i > 0; i--)
            heapify(i);
    }
    void print()
    {
        for (int i = 1; i < queueLength + 1; i++)
            cout << *queue[i] << " ";
        cout << "\n";
    }
};

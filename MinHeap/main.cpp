#include <iostream>
#include "BHeap.h"
#include "Minheap.h"
#define MAX_SIZE 10

int main()
{
    int **array = new int *[MAX_SIZE];
    for (int i = 1; i < MAX_SIZE; i++)
        array[i] = new int(i);
    MinHeap<int> *pippo = new MinHeap<int>(array, MAX_SIZE, 5);
    pippo->print();
    cout << "extract da' " << *pippo->extract() << "\n";
    pippo->print();
}
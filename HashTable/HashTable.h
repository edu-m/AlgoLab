#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <math.h>
using namespace std;

template <class T>
class HashTable
{
    list<T> *table;
    int size;  // numero di nodi occupati
    int slots; // numero di posti occupabili
    int div_hash(T key)
    {
        return int(key) % this->slots;
    }

public:
    int getSize()
    {
        return this->size;
    }
    int getSlots()
    {
        return this->slots;
    }
    HashTable<T>(int _slots)
    {
        this->slots = _slots;
        this->size = 0;
        table = new list<T>[this->slots];
    }
    HashTable<T>(int _slots, int _size, T *data)
    {
        this->slots = _slots;
        table = new list<T>[this->slots];
        for (int i = 0; i < _size; i++)
        {
            this->insertKey(data[i]);
        }
    }
    HashTable<T> *insertKey(T key)
    {
        table[div_hash(key)].push_back(key);
        ++size;
        return this;
    }
    void print()
    {
        for (int i = 0; i < this->slots; i++)
        {
            typename list<T>::iterator it;
            for (it = table[i].begin(); it != table[i].end(); it++)
                cout << *it << " ";
            cout << "\n";
        }
    }
    void print_output()
    {
        ofstream file;
        file.open("output.txt", std::ofstream::out | std::ofstream::app);
        for (int i = 0; i < slots; i++)
        {
            file << this->table[i].size() << " ";
            // if (i < slots - 1)
            //     file << " ";
        }
        file << "\n";
    }
};

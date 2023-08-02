#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
void Heapify(vector<T> &_queue, int heapsize, int i, int &heapifyCount)
{
    ++heapifyCount;
    int min = i;
    int l = 2 * i + 1; // offset di 1 per considerare la posizione 0 valida
    int r = 2 * i + 2;

    if (l < heapsize && _queue[l] < _queue[min])
        min = l;

    if (r < heapsize && _queue[r] < _queue[min])
        min = r;

    if (min != i)
    {
        swap(_queue[i], _queue[min]);
        Heapify(_queue, heapsize, min, heapifyCount);
    }
}

template <class T>
int HeapSort(vector<T> &_queue)
{
    int n = _queue.size();
    int heapifyCount = 0;

    for (int i = n / 2 - 1; i >= 0; i--) // faccio il build heap
        Heapify(_queue, n, i, heapifyCount);

    for (int i = n - 1; i > 0; i--) // eseguo l'heapsort effettivo
    {
        swap(_queue[0], _queue[i]);
        Heapify(_queue, i, 0, heapifyCount);
    }

    return heapifyCount;
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    for (int task = 0; task < 100; ++task)
    {
        string dataType;
        int size;
        inputFile >> dataType >> size;

        if (dataType == "double")
        {
            vector<double> inputVector(size);
            vector<double> temp(size);
            for (int i = 0; i < size; i++)
                inputFile >> temp[i];
            inputVector.assign(temp.begin(), temp.end());
            int heapifyCount = HeapSort(inputVector);
            outputFile << heapifyCount << " ";
            for (int i = 0; i < inputVector.size(); i++)
                outputFile << inputVector[i] << " ";
            outputFile << endl;
        }
        else if (dataType == "bool")
        {
            vector<bool> inputVector(size);
            vector<bool> temp(size);
            for (int i = 0; i < size; i++)
            {
                int val;
                inputFile >> val;
                temp[i] = (val != 0);
            }
            inputVector.assign(temp.begin(), temp.end());
            int heapifyCount = HeapSort(inputVector);
            outputFile << heapifyCount << " ";
            for (int i = 0; i < inputVector.size(); i++)
                outputFile << inputVector[i] << " ";
            outputFile << endl;
        }
        else if (dataType == "char")
        {
            vector<char> inputVector(size);
            vector<char> temp(size);
            for (int i = 0; i < size; i++)
                inputFile >> temp[i];
            inputVector.assign(temp.begin(), temp.end());
            int heapifyCount = HeapSort(inputVector);

            outputFile << heapifyCount << " ";
            for (int i = 0; i < inputVector.size(); i++)
                outputFile << inputVector[i] << " ";
            outputFile << endl;
        }
        else
        {
            vector<int> inputVector(size);
            for (int i = 0; i < size; i++)
                inputFile >> inputVector[i];
            int heapifyCount = HeapSort(inputVector);
            outputFile << heapifyCount << " ";
            for (int i = 0; i < inputVector.size(); i++)
                outputFile << inputVector[i] << " ";
            outputFile << endl;
        }
    }
}

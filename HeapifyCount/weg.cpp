#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Funzione per scambiare due elementi in un vettore
// template <typename T> void swap(T &a, T &b) {
//   T temp = a;
//   a = b;
//   b = temp;
// }

// Procedura per mantenere la proprietà di MaxHeap
template <class T>
void MaxHeapify(vector<T> &arr, int size, int i, int &heapifyCalls) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < size && arr[left] > arr[largest])
    largest = left;

  if (right < size && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapifyCalls++;
    MaxHeapify(arr, size, largest, heapifyCalls);
  }
}

// Procedura per costruire il MaxHeap
template <typename T> void BuildMaxHeap(vector<T> &arr, int &heapifyCalls) {
  int size = arr.size();
  for (int i = size / 2 - 1; i >= 0; i--)
    MaxHeapify(arr, size, i, heapifyCalls);
}

// Estrazione dell'elemento con la massima priorità
template <typename T> T ExtractMax(vector<T> &arr, int &heapifyCalls) {
  T maxVal = arr[0];
  arr[0] = arr[arr.size() - 1];
  arr.pop_back();
  MaxHeapify(arr, arr.size(), 0, heapifyCalls);
  return maxVal;
}

int main() {
  ifstream inputFile("input.txt");
  ofstream outputFile("output.txt");

  int heapifyCalls;

  while (!inputFile.eof()) {
    string type;
    int N;

    inputFile >> type >> N;

    if (type == "int") {
      vector<int> arr(N);
      for (int i = 0; i < N; i++)
        inputFile >> arr[i];

      heapifyCalls = 0;
      BuildMaxHeap(arr, heapifyCalls);

      for (int i = 0; i < N; i++)
        ExtractMax(arr, heapifyCalls);

      outputFile << heapifyCalls << endl;
    } else if (type == "double") {
      vector<double> arr(N);
      for (int i = 0; i < N; i++)
        inputFile >> arr[i];

      heapifyCalls = 0;
      BuildMaxHeap(arr, heapifyCalls);

      for (int i = 0; i < N; i++)
        ExtractMax(arr, heapifyCalls);

      outputFile << heapifyCalls << endl;
    } else if (type == "char") {
      vector<char> arr(N);
      for (int i = 0; i < N; i++)
        inputFile >> arr[i];

      heapifyCalls = 0;
      BuildMaxHeap(arr, heapifyCalls);

      for (int i = 0; i < N; i++)
        ExtractMax(arr, heapifyCalls);

      outputFile << heapifyCalls << endl;
    } else if (type == "bool") {
      vector<bool> arr(N);
      for (int i = 0; i < N; i++) {
        int val;
        inputFile >> val;
        arr[i] = val;
      }

      heapifyCalls = 0;
      BuildMaxHeap(arr, heapifyCalls);

      for (int i = 0; i < N; i++)
        ExtractMax(arr, heapifyCalls);

      outputFile << heapifyCalls << endl;
    }
  }

  inputFile.close();
  outputFile.close();

  return 0;
}

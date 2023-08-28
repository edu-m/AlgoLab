#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int heapifyCount;

// Struttura per rappresentare una coppia di valori (x, y)
struct Pair {
  int x;
  int y;
};

// Funzione per effettuare lo scambio tra due coppie di valori
void swapPairs(Pair &a, Pair &b) {
  Pair temp = a;
  a = b;
  b = temp;
}

bool compare(Pair &a, Pair &b) {
  return (a.x > b.x || (a.x == b.x && a.y > b.y));
}

// Funzione per eseguire il passo Heapify dell'HeapSort
void heapify(std::vector<Pair> &arr, int n, int i) {
  heapifyCount++;
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n) {

    if (compare(arr[left], arr[largest])) {
      largest = left;
    }
  }

  if (right < n) {

    if (arr[right].x > arr[largest].x ||
        (arr[right].x == arr[largest].x && arr[right].y > arr[largest].y)) {
      largest = right;
    }
  }

  if (largest != i) {
    swapPairs(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

// Funzione per eseguire l'HeapSort
void heapSort(std::vector<Pair> &arr, int n) {

  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }

  for (int i = n - 1; i > 0; i--) {
    swapPairs(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

int main() {
  std::ifstream inputFile("input.txt");
  std::ofstream outputFile("output.txt");

  if (!inputFile || !outputFile) {
    std::cerr << "Errore nell'apertura dei file." << std::endl;
    return 1;
  }

  for (int task = 0; task < 3; task++) {
    heapifyCount = 0;
    std::string dataType;
    int n;
    inputFile >> dataType >> n;

    std::vector<Pair> pairs(n);
    for (int i = 0; i < n; i++) {
      char c;
      inputFile >> c >> pairs[i].x >> c >> pairs[i].y >> c;
    }

    heapSort(pairs, n);

    outputFile << heapifyCount;
    for (const Pair &p : pairs) {
      outputFile << " (" << p.x << "," << p.y << ")";
    }
    outputFile << std::endl;
  }

  inputFile.close();
  outputFile.close();

  return 0;
}

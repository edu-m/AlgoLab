#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>
using namespace std;
#define TASK 1
#define INF 1001

int calcolaResto(int R, int N, const vector<int> &tagli)
{
    vector<vector<int>> matrix(N + 1, vector<int>(R + 1, INF));

    for (int i = 0; i <= N; ++i) // inizializzo tutta la prima colonna a 0
        matrix[i][0] = 0;

    for (int i = 1; i <= N; ++i) // scorro per ciascun taglio disponibile ogni numero fino ad arrivare al resto
    {
        for (int j = 1; j <= R; ++j)
        {
            if (j >= tagli[i - 1])
                matrix[i][j] = min(1 + matrix[i][j - tagli[i - 1]], matrix[i - 1][j]);
            else
                matrix[i][j] = matrix[i - 1][j];
        }
#if 1
        for (int k = 0; k <= N; k++)
        {
            for (int h = 0; h <= R; h++)
            {
                if (matrix[k][h] == INF)
                    cout << "INF"
                         << "\t";
                else
                    cout << matrix[k][h] << "\t";
            }
            cout << endl;
        }
        cout << endl;
#endif
    }

    return matrix[N][R];
}

int main()
{
    int R, N;
    vector<int> tagli;
    ifstream input("input.txt");
    ofstream output("output.txt");

    for (int i = 0; i < TASK; i++)
    {
        input >> R >> N;
        tagli.resize(N);
        for (int i = 0; i < N; ++i)
            input >> tagli[i];
        int result = calcolaResto(R, N, tagli);
        output << result << endl;
    }
}
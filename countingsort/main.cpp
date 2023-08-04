#include <vector>
#include <iostream>
#include <fstream>
#include <climits>
#define TASK 100
using namespace std;

int find_min(vector<int> &vec)
{
    int min = INT_MAX;
    for (int i = 0; i < vec.size(); i++)
        if (min > vec[i])
            min = vec[i];
    return min;
}

int find_max(vector<int> &vec)
{
    int max = -1;
    for (int i = 0; i < vec.size(); i++)
        if (max < vec[i])
            max = vec[i];
    return max;
}

vector<int> countingsort(vector<int> &A)
{
    int max = find_max(A);
    int min = find_min(A);
    int var = max - min;
    // cout << max << " " << min << " "<<var<<endl;
    vector<int> C = vector<int>(var + 1, 0);
    vector<int> B = vector<int>(A.size(), 0);
    for (int i = 0; i < A.size(); i++) // trovo C
        ++C[A[i] - min];
    for (int i = 1; i < var+1; i++) // trovo C'
    {
        C[i] += C[i - 1];
        
    }
    cout << "0 ";
    for(int i=0;i<var;i++){
        cout <<C[i] << " ";
    }

    for (int i = B.size() - 1; i >= 0; i--)
    {
        B[C[A[i] - min] - 1] = A[i];
        C[A[i] - min]--;
    }
    return B;
}

int main()
{
    ifstream input("input.txt");
    int number;
    int temp;
    vector<int> array;
    for (int i = 0; i < TASK; i++)
    {
        array.resize(0);
        input >> number;
        for (int j = 0; j < number; j++)
        {
            input >> temp;
            array.push_back(temp);
        }
        vector<int> sorted = countingsort(array);
        for (int j = 0; j < number; j++)
         cout << sorted[j] << " ";
         cout << endl;
    }
}
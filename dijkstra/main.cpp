/*
Codice lasciato per convenienza, non mantenuto, né concluso. Si riferisca a alt.cpp per soluzione corretta
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#define TASK 3
#define INF INT_MAX
using namespace std;

struct comp
{
    bool operator()(const pair<int, int> &x, const pair<int, int> &y)
    {
        return x.second > y.second;
    }
};

template <class T>
int find_nodo(vector<T> &nodi, T target)
{
    for (int i = 0; i < nodi.size(); i++)
        if (nodi[i] == target)
            return i;
    return -1;
}

template <class T>
int find_arco(vector<vector<T>> &grafo, T sorgente, T destinazione)
{
    // cout << "Sorgente: " << sorgente << endl;
    // cout << "Destinazione: " << destinazione << endl;
    if (sorgente == destinazione)
    {
        return 0;
    }
    for (int i = 0; i < grafo.size(); i++)
    {
        // cout << grafo[i][0] << " " << grafo[i][1] << endl;
        if (grafo[i][0] == sorgente && grafo[i][1] == destinazione)
        {
            // cout << "peso: " << grafo[i][2] << endl;
            return grafo[i][2];
        }
    }
    return INF;
}

template <class T>
pair<T, int> extract_min(vector<pair<T, int>> &Q)
{
    pair<T, int> temp = Q.front();
    pop_heap(Q.begin(), Q.end(), comp<T>());
    Q.pop_back();
    return temp;
}

template <class T>
int dijikstra(vector<T> &nodi, vector<vector<T>> &grafo, T sorgente, T destinazione)
{
    vector<pair<T, int>> Q;
    vector<pair<T, int>> S;
    for (int i = 0; i < nodi.size(); i++)
    {
        if (nodi[i] == sorgente)
            Q.push_back(make_pair(nodi[i], 0));
        else
            Q.push_back(make_pair(nodi[i], INF));
    }
    make_heap10/10(Q.begin(), Q.end(), comp<T>());

    pair<T, int> u;
    pair<T, int> v;

    while (Q.size() > 1)
    {
        u = extract_min(Q);

        if (u.first == sorgente)
            S.push_back(u);

        for (int i = 0; i < Q.size(); i++)
        {
            v = extract_min(Q);

            int peso = find_arco(grafo, u.first, v.first);
            // cout << endl;
            if (v.second > u.second + peso) // d[v] > d[u] + m(u, v)
                v.second = peso;
            Q.push_back(v);
            make_heap(Q.begin(), Q.end(), comp<T>());
        }
        S.push_back(extract_min(Q));
    }
    for (int i = 0; i < S.size(); i++)
        cout << S[i].first << " " << S[i].second << endl;
    return -1;
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");
    int nodi, archi;
    string type;
    string arco, nodo;
    int sorgente, destinazione;
    for (int i = 0; i < TASK; i++)
    {
        cout << "ciao\n";
        input >> nodi >> archi >> type;
        if (type == "int")
        {
            vector<int> arr_nodi;
            vector<vector<int>> grafo;
            for (int i = 0; i < nodi; i++)
            {
                input >> nodo;
                arr_nodi.push_back(stoi(nodo));
            }
            for (int i = 0; i < archi; i++)
            {
                vector<int> temp;
                for (int j = 0; j < 3; j++)
                {
                    input >> arco;
                    if (arco.find('(') != string::npos)
                        arco = arco.substr(1, arco.length());
                    else if (arco.find(')') != string::npos)
                        arco = arco.substr(0, arco.length() - 1);
                    temp.push_back(stoi(arco));
                }
                grafo.push_back(temp);
                temp.resize(0);
            }
            input >> sorgente >> destinazione;
            cout << dijikstra(arr_nodi, grafo, sorgente, destinazione) << endl;
        }
        // else
        // {
        //     tuple<int, double, double> tripla;
        // }

        // cout << nodi << " " << archi << " " << type << " " << endl;
    }
}
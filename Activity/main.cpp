#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#define TASK 100
using namespace std;

struct comp
{
    bool operator()(const pair<int, int> &x, const pair<int, int> &y) const
    {
        return x.second < y.second;
    }
};

int activitySelection(vector<pair<int, int>> &activities)
{
    int card = 1;
    int i = 0;
    for (int m = 1; m < activities.size(); m++)
    {
        if (activities[m].first >= activities[i].second)
        {
            ++card;
            i = m;
        }
    }
    return card;
}

int main()
{
    int number;
    ifstream input("input.txt");
    ofstream output("output.txt");
    vector<pair<int, int>> activities;
    string temp0, temp1;
    pair<int, int> activity;
    for (int i = 0; i < TASK; i++)
    {
        activities.resize(0);
        input >> number;
        for (int j = 0; j < number; j++) // ciclo di input di dati da input.txt
        {
            input >> temp0 >> temp1;
            temp0 = temp0.substr(1, temp0.length());
            temp1 = temp1.substr(0, temp1.length() - 1);
            activity.first = stoi(temp0);
            activity.second = stoi(temp1);
            activities.push_back(activity);
            // cout << activities[j].first << " " << activities[j].second << endl;
        }
        sort(activities.begin(), activities.end(), comp());
        // for (int j = 0; j < number; j++)
        //     cout << activities[j].first << " " << activities[j].second << endl;
        output << activitySelection(activities)<<endl;
    }
}
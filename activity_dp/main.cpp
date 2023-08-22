#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Activity {
  int start;
  int end;
};

bool compareActivities(const Activity &a, const Activity &b) {
  return a.end < b.end;
}

int maximizeResourceUtilization(vector<Activity> &activities) {
  int n = activities.size();
  vector<int> dp(n, 0);

  dp[0] = activities[0].end - activities[0].start;

  for (int i = 1; i < n; ++i) {
    dp[i] = max(dp[i - 1], activities[i].end - activities[i].start);

    for (int j = i - 1; j >= 0; --j) {
      if (activities[j].end <= activities[i].start) {
        dp[i] = max(dp[i], dp[j] + activities[i].end - activities[i].start);
        break;
      }
    }
  }

  return dp[n - 1];
}

int main() {
  int numTasks = 100;
  ifstream input("input.txt");
  ofstream output("output.txt");

  for (int t = 0; t < numTasks; ++t) {
    int numActivities;
    input >> numActivities;

    vector<Activity> activities(numActivities);
    for (int i = 0; i < numActivities; ++i) {
      char delimiter;
      input >> delimiter; // Read '('
      input >> activities[i].start;

      input >> activities[i].end;
      input >> delimiter; // Read ')'
    }

    sort(activities.begin(), activities.end(), compareActivities);

    output << maximizeResourceUtilization(activities)<<endl;
  }

  return 0;
}

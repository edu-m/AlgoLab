#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int INF = 1e9;

int main() {
    int num_tasks = 100;
    ifstream input("input.txt");
    for (int task = 0; task < num_tasks; ++task) {
        int R, N;
        input >> R >> N;

        vector<int> T(N);
        for (int i = 0; i < N; ++i) {
            input >> T[i];
        }

        vector<int> dp(R + 1, INF);
        dp[0] = 0;

        for (int i = 1; i <= R; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i >= T[j]) {
                    dp[i] = min(dp[i], dp[i - T[j]] + 1);
                }
            }
        }

        cout << dp[R] << endl;
    }

    return 0;
}

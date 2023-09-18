#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define TASK 100
using namespace std;

struct Game {
  int day, start, end, cost, reward;
};

// Funzione per ordinare le partite per l'orario di fine
bool compareGames(const Game &a, const Game &b) {
  if (a.day == b.day)
    return a.end < b.end;
  return a.day < b.day;
}

int main() {
  ifstream input("input.txt");
  ofstream output("output.txt");
  for (int t = 0; t < TASK; t++) {
    int N, M;
    input >> N >> M;

    vector<Game> games(N);

    for (int i = 0; i < N; i++) {
      input >> games[i].day >> games[i].start >> games[i].end >>
          games[i].cost >> games[i].reward;
    }

    // Ordina le partite per l'orario di fine
    sort(games.begin(), games.end(), compareGames);

    // Array dinamico per tenere traccia del guadagno massimo
    vector<int> dp(25 * 101, -1); // 24 ore * 100 giorni + 1
    dp[0] = M;                    // Budget iniziale

    int ans = M;

    for (const auto &game : games) {
      int currentTime = game.day * 24 + game.end;
      int startTime = game.day * 24 + game.start;

      for (int prevTime = 0; prevTime <= startTime; prevTime++) {
        if (dp[prevTime] < game.cost)
          continue;

        // Calcola il guadagno massimo se partecipi a questa partita
        int newProfit = dp[prevTime] - game.cost + game.reward;

        // Aggiorna il guadagno massimo possibile per l'orario di fine della
        // partita
        dp[currentTime] = max(dp[currentTime], newProfit);

        // Aggiorna il guadagno massimo globale
        ans = max(ans, newProfit);
      }
    }

    output << ans << endl;
  }
}

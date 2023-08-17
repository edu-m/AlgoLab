def levenshtein_distance(X, Y):
    N, M = len(X), len(Y)
    dp = [[0 for _ in range(M+1)] for _ in range(N+1)]

    for i in range(N+1):
        dp[i][0] = i

    for j in range(M+1):
        dp[0][j] = j

    for i in range(1, N+1):
        for j in range(1, M+1):
            if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1

    return dp[N][M]

# Lettura dell'input
with open('input.txt', 'r') as file:
    input_data = file.readlines()

# Elaborazione dei task e scrittura dell'output
output_data = []
for line in input_data:
    N, M, X, Y = line.split()
    N, M = int(N), int(M)
    distance = levenshtein_distance(X, Y)
    output_data.append(str(distance))

with open('output.txt', 'w') as file:
    file.write('\n'.join(output_data))

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 10

int n;
int graph[MAXN][MAXN];
bool visited[MAXN];
int bestPath[MAXN + 1], currentPath[MAXN + 1];
int minCost = INT_MAX;

bool isLexicographicallySmaller(int *path1, int *path2) {
    for (int i = 0; i < n; i++) {
        if (path1[i] < path2[i]) 
            return true;
        if (path1[i] > path2[i]) 
            return false;
    }
    return false;
}

void dfs(int node, int count, int cost) {
    if (count == n) {
        if (graph[node][0] != -1) {  
            cost += graph[node][0];
            currentPath[n] = 0; 

            if (cost < minCost || (cost == minCost && isLexicographicallySmaller(currentPath, bestPath))) {
                minCost = cost;
                for (int i = 0; i <= n; i++)
                    bestPath[i] = currentPath[i];
            }
        }
        return;
    }

    for (int next = 0; next < n; next++) {
        if (!visited[next] && graph[node][next] != -1) {
            visited[next] = true;
            currentPath[count] = next;
            dfs(next, count + 1, cost + graph[node][next]);
            visited[next] = false; 
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    for (int i = 0; i < MAXN; i++)
        visited[i] = false;

    visited[0] = true;
    currentPath[0] = 0;
    dfs(0, 1, 0);

    if (minCost == INT_MAX) {
        printf("The path doesn't exist\n");
    } else {
        printf("Minimum Cost: %d\n", minCost);
        printf("Optimal Path: ");
        for (int i = 0; i <= n; i++)
            printf("%d ", bestPath[i]);
        printf("\n");
    }

    return 0;
}

/*
OUTPUT ->>
rithvikmatta@penguin:~/sem4/DAA$ gcc bananaProb.c 
rithvikmatta@penguin:~/sem4/DAA$ ./a.out
4
0
1
15
6
2
0
7
3
9
6
0
12
10
4
8
0
Minimum Cost: 21
Lexicographically Smallest Path: 0 1 3 2 0 */
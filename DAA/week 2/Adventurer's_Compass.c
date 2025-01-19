// The adventurer has discovered a map leading to hidden treasure, but the coordinates of the potential treasure locations are not aligned with his compass grid. Each point on the map represents a potential treasure location, with x and y values that could be scattered across the grid. To align these points with the adventurer’s compass, you must adjust the coordinates so that the smallest x-coordinate and the smallest y-coordinate become the new origin (0, 0).

// Your task is to translate the entire map in such a way that the point with the lowest x and y values moves to the origin, and all other points are adjusted accordingly while maintaining their relative positions. This transformation will allow the adventurer to better understand the map and navigate to the treasure efficiently.

// BoilerPlate:

// #include <stdio.h>
// void adjustCoordinates(int coordinates[][2], int n) {
//     \\ Enter your code here	
// }

// void printCoordinates(int coordinates[][2], int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d %d\n", coordinates[i][0], coordinates[i][1]);
//     }
// }

// int main() {
//     int n;
//     scanf("%d", &n); 
//     int coordinates[n][2];
//     for (int i = 0; i < n; i++) {
//         scanf("%d %d", &coordinates[i][0], &coordinates[i][1]);
//     }
//     adjustCoordinates(coordinates, n);
//     printCoordinates(coordinates, n);
//     return 0;
// }
// Input Format

// The first line contains a single integer n,the number of 2D coordinates.
// The next n lines each contain two space-separated integers x and y, representing the coordinates of a point on the map.
// Constraints

// The number of coordinates n, (1 ≤ n≤ 10^4)
// The coordinates x and y, (−10^4 ≤ x, y ≤ 10^4)
// Output Format

// Output n lines where each line contains two integers representing the adjusted coordinates. Each coordinate pair should be printed on a new line.

// Sample Input 0

// 3
// 2 3
// 5 8
// 1 6
// Sample Output 0

// 1 0
// 4 5
// 0 3
// Explanation 0

// Find the new origin. To align the map, we must identify the smallest x-coordinate and the smallest y-coordinate among the points:

// The smallest x-coordinate is 1 The smallest y-coordinate is 3.

// Thus, the new origin is (1,3).

// Find relative position from the new origin:

// (2,3) - (1, 3) = (1, 0)
// (5, 8) - (1, 3) = (4, 5)
// (1, 6) - (1, 3) = (0, 3)

#include <stdio.h>
void printCoordinates(int coordinates[][2], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", coordinates[i][0], coordinates[i][1]);
    }
}

void adjustCoordinates(int coordinates[][2], int n) {
    int minx = coordinates[0][0]; 
    int miny = coordinates[0][1]; 
    for (int i = 1; i < n; i++) {
        if (coordinates[i][0] < minx) {
            minx = coordinates[i][0];
        }
        if (coordinates[i][1] < miny) {
            miny = coordinates[i][1];
        }
    }
    for (int i = 0; i < n; i++) { 
        coordinates[i][0] = coordinates[i][0] - minx; 
        coordinates[i][1] = coordinates[i][1] - miny; 
    }
}



int main() {
    int n;
    scanf("%d", &n); 
    int coordinates[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coordinates[i][0], &coordinates[i][1]);
    }
    adjustCoordinates(coordinates, n);
    printCoordinates(coordinates, n);
    return 0;
}
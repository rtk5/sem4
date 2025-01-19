// In the Labyrinth of Numbers, a magical lock requires the adventurer to determine the number of possible sequences of positive integers that sum up to a given number N. The sequence must use only positive integers. The order of integers in the sequence matters. For example, (2+1 is considered different from 1+2). Your task is to calculate the total number of such sequence using recursion.

// Boilerplate code:

// #include<stdio.h>
// int totalCombinations(int n) {
//   // Enter your code here
// }
// int main() {
//     int n;
//     scanf("%d", &n);
//     int result = totalCombinations(n);
//     printf("%d\n",result);
//     return 0;
// }
// Input Format

// A single integer N.

// Constraints

// 1≤N≤100

// Output Format

// A single integer.

// Sample Input 0

// 5
// Sample Output 0

// 16
// Explanation 0

// List all possible ways to split the number 5 into sums of positive integers.

// Each sequence is distinct based on the order of numbers.

// Sequences with one number: [5]
// Sequences with two numbers: [4,1],[3,2],[2,3],[1,4]
// Sequences with three numbers: [3,1,1],[2,2,1],[1,3,1],[1,2,2],[2,1,2],[1,1,3]
// Sequences with four numbers: [2,1,1,1],[1,2,1,1],[1,1,2,1],[1,1,1,2]
// Sequences with five numbers: [1,1,1,1,1]
// The total number of ways of forming the sum 5 is 16

// Sample Input 1

// 1
// Sample Output 1

// 1
// Explanation 1

// Number of ways to make a sum of 1, using positive integers is 1.

#include <stdio.h>

int totalCombinations(int n) {
    if (n == 0) {
        return 1; 
    }
    if (n < 0) {
        return 0;
    }
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        count += totalCombinations(n - i); 
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = totalCombinations(n);
    printf("%d\n", result);
    return 0;
}
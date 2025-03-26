// Write a C Program to demo the Optimal page replacement algorithm

#include <stdio.h>

int findOptimal(int rs[], int m[], int f, int n, int index) {
    int farthest = index, replaceIndex = -1;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (m[i] == rs[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (replaceIndex == -1) ? 0 : replaceIndex;
}

int main() {
    int n, f, rs[25], m[10], pf = 0;
    printf("\n Enter length of the reference string: ");
    scanf("%d", &n);
    printf("\n Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
    }
    printf("\n Enter the number of frames: ");
    scanf("%d", &f);
    for (int i = 0; i < f; i++) {
        m[i] = -1;
    }
    
    printf("\n The Optimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (m[j] == rs[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            int replaceIndex;
            for (replaceIndex = 0; replaceIndex < f; replaceIndex++) {
                if (m[replaceIndex] == -1) {
                    break;
                }
            }
            if (replaceIndex == f) {
                replaceIndex = findOptimal(rs, m, f, n, i + 1);
            }
            m[replaceIndex] = rs[i];
            pf++;
        }
        
        for (int j = 0; j < f; j++) {
            printf("%d\t", m[j]);
        }
        if (!found) printf("PF No.%d", pf);
        printf("\n");
    }
    
    printf("\n The number of Page Faults using Optimal Page Replacement are %d\n", pf);
    printf("\n The number of Page Hits using Optimal Page Replacement are %d\n",n-pf);
    return 0;
}

#include <stdio.h>
void sortProcessesByPriority(int processes[], int n, int bt[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                int tempPriority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = tempPriority;

                int tempBT = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = tempBT;

                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;
            }
        }
    }
}

void findWaitingTime(int processes[], int n, int wt[], int bt[]) {
    wt[0] = 0; 
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int wt[], int bt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    sortProcessesByPriority(processes, n, bt, priority);
    findWaitingTime(processes, n, wt, bt);
    findTurnAroundTime(processes, n, wt, bt, tat);

    printf("Processes Burst Time Waiting Time Turnaround Time Priority\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d %d %d %d %d\n", processes[i], bt[i], wt[i], tat[i], priority[i]);
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {10, 5, 8};
    int priority[] = {5, 2, 3};

    findAvgTime(processes, n, burst_time, priority);
    return 0;
}

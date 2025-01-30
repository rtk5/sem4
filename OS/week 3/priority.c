#include <stdio.h>
void sortProcessesByPriority(int processes[], int n, int bt[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                int temppriority = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temppriority;
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;
            }
        }
    }
}

void findwtTime(int processes[], int n, int wt[], int bt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)    {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findtatTime(int processes[], int n, int wt[], int bt[], int tat[]) {
    for (int i = 0; i < n; i++)    {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[], int priority[]) {
    int wt[n], tat[n], tot_wt = 0, tot_tat = 0;
    sortProcessesByPriority(processes, n, bt, priority);
    findwtTime(processes, n, wt, bt);
    findtatTime(processes, n, wt, bt, tat);
    printf("Processes BurstTime WaitingTime TurnaroundTime Priority\n");
    for (int i = 0; i < n; i++)    {
        tot_wt += wt[i];
        tot_tat += tat[i];
        printf(" %d\t  %d\t \t   %d\t\t    %d\t   %d\n", processes[i], bt[i], wt[i], tat[i], priority[i]);
    }
    float avg_wt = (float)tot_wt / (float)n;
    float avg_tat = (float)tot_tat / (float)n;
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3, 4 , 5};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {10, 5, 8, 6, 4};
    int priority[] = {5, 2, 3, 8, 7};
    findavgTime(processes, n, burst_time, priority);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct process {
    int id;
    int arrival_time;
    int burst;
    int starting_time;
    int completion_time;
    int turn_around;
    int response_time;
    int waiting_time;
    int finished;
} process;

int main() {
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    process P[n];
    printf("Enter Arrival Time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i].arrival_time);
        P[i].id = i;
        P[i].finished = 0;
    }

    printf("Enter Burst Time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i].burst);
    }

    int time = 0, completed = 0;
    float total_wait = 0, total_tat = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!P[i].finished && P[i].arrival_time <= time) {
                if (P[i].burst < min_burst) {
                    min_burst = P[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        P[idx].starting_time = time;
        P[idx].completion_time = time + P[idx].burst;
        P[idx].turn_around = P[idx].completion_time - P[idx].arrival_time;
        P[idx].response_time = P[idx].starting_time - P[idx].arrival_time;
        P[idx].waiting_time = P[idx].turn_around - P[idx].burst;
        P[idx].finished = 1;

        time = P[idx].completion_time;
        completed++;

        total_wait += P[idx].waiting_time;
        total_tat  += P[idx].turn_around;
    }

    printf("\n===== Process Table (SJF Non-Preemptive) =====\n");
    printf("%-10s %-10s %-10s %-10s %-15s %-12s %-10s %-10s\n",
           "Process", "Arrival", "Burst", "Start", "Completion", "Response", "TAT", "Waiting");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-10d %-10d %-10d %-15d %-12d %-10d %-10d\n",
               P[i].id, P[i].arrival_time, P[i].burst,
               P[i].starting_time, P[i].completion_time,
               P[i].response_time, P[i].turn_around, P[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wait / n);

    return 0;
}

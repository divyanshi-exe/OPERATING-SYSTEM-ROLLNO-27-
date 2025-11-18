#include <stdio.h>

typedef struct {
    int id, bt, at;
    int ct, tat, wt, rt, rem, finished, first_exec;
} Process;

int main() {
    int n, tq = 2;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process P[n];
    printf("Enter Burst Time: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i].bt);
        P[i].rem = P[i].bt;
        P[i].finished = 0;
        P[i].first_exec = -1;
        P[i].id = i;
    }
    printf("Enter Arrival Time: ");
    for (int i = 0; i < n; i++) scanf("%d", &P[i].at);

    int time = 0, done = 0;
    float total_wt = 0, total_tat = 0;
    int q[1000], front = 0, rear = 0;
    int inq[n];
    for (int i = 0; i < n; i++) inq[i] = 0;

    printf("\nGantt Chart: ");
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (P[i].at <= time && !P[i].finished && !inq[i]) {
                q[rear++] = i;
                inq[i] = 1;
            }
        }
        if (front == rear) { time++; continue; }

        int idx = q[front++];
        if (P[idx].first_exec == -1) P[idx].first_exec = time;

        printf("P%d ", P[idx].id);

        if (P[idx].rem > tq) {
            P[idx].rem -= tq;
            time += tq;
        } else {
            time += P[idx].rem;
            P[idx].rem = 0;
            P[idx].ct = time;
            P[idx].tat = P[idx].ct - P[idx].at;
            P[idx].wt = P[idx].tat - P[idx].bt;
            P[idx].rt = P[idx].first_exec - P[idx].at;
            P[idx].finished = 1;
            total_wt += P[idx].wt;
            total_tat += P[idx].tat;
            done++;
        }

        for (int i = 0; i < n; i++) {
            if (P[i].at <= time && !P[i].finished && !inq[i]) {
                q[rear++] = i;
                inq[i] = 1;
            }
        }

        if (!P[idx].finished) {
            q[rear++] = idx;
        }
    }

    printf("\nAverage waiting time: %.2f\n", total_wt / n);
    printf("Average turnaround time: %.2f\n", total_tat / n);

    return 0;
}

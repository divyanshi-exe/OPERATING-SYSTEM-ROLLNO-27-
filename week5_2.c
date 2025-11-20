#include <stdio.h>
#include <stdbool.h>

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int max[p][r], alloc[p][r], need[p][r], total[r], avail[r];

    printf("Enter maximum requirement matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter total resources vector:\n");
    for (int j = 0; j < r; j++)
        scanf("%d", &total[j]);

    for (int j = 0; j < r; j++) {
        int sum = 0;
        for (int i = 0; i < p; i++)
            sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    bool finish[p];
    for (int i = 0; i < p; i++) finish[i] = false;

    int count = 0;

    while (count < p) {
        bool found = false;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i][j] > avail[j])
                        break;
                if (j == r) {
                    for (int k = 0; k < r; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    if (count == p)
        printf("\nNo deadlock detected\n");
    else
        printf("\nDeadlock detected\n");

    return 0;
}

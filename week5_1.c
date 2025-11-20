#include <stdio.h>
#include <stdbool.h>

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int max[p][r], alloc[p][r], need[p][r], total[r], avail[r];

    printf("Enter Max matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Total instances of each resource:\n");
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

    int safeSeq[p], count = 0;

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
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }

    if (count == p) {
        printf("\nRequest can be fulfilled\nSafe Sequence: ");
        for (int i = 0; i < p; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nRequest cannot be fulfilled\n");
    }

    return 0;
}


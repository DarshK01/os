#include <stdio.h>

#define MAX 5  // Number of processes

struct Process {
    int id, arrival, burst, priority, completion, turnaround, waiting, remaining;
};

void priorityScheduling(struct Process p[], int n) {
    int time = 0, completed = 0, min_priority_index;

    while (completed < n) {
        min_priority_index = -1;
        int min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                min_priority_index = i;
            }
        }

        if (min_priority_index != -1) {
            p[min_priority_index].remaining--;

            if (p[min_priority_index].remaining == 0) {
                p[min_priority_index].completion = time + 1;
                p[min_priority_index].turnaround = p[min_priority_index].completion - p[min_priority_index].arrival;
                p[min_priority_index].waiting = p[min_priority_index].turnaround - p[min_priority_index].burst;
                completed++;
            }
        }
        time++;
    }
}

void displayResults(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].arrival, p[i].burst, p[i].priority,
               p[i].completion, p[i].turnaround, p[i].waiting);
        total_tat += p[i].turnaround;
        total_wt += p[i].waiting;
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
}

int main() {
    struct Process p[MAX] = {
        {1, 0, 11, 2, 0, 0, 0, 11},
        {2, 5, 28, 0, 0, 0, 0, 28},
        {3, 12, 2, 3, 0, 0, 0, 2},
        {4, 2, 10, 1, 0, 0, 0, 10},
        {5, 9, 16, 4, 0, 0, 0, 16}
    };

    priorityScheduling(p, MAX);
    displayResults(p, MAX);

    return 0;
}

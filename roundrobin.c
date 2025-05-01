#include <stdio.h>
#define MAX 3  // Number of processes
#define QUANTUM 4  // Time Quantum
struct Process {
    int id, burst, remaining, completion, turnaround, waiting;
};
void roundRobinScheduling(struct Process p[], int n, int quantum) {
    int time = 0, done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                done = 0;
                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    p[i].remaining = 0;
                }
            }
        }
    } while (!done);
}
void displayResults(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;

    printf("\nProcess ID\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               p[i].id, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        total_tat += p[i].turnaround;
        total_wt += p[i].waiting;
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);}
    int main() {
    struct Process p[MAX] = {
        {1, 24, 24, 0, 0, 0},
        {2, 3, 3, 0, 0, 0},
        {3, 3, 3, 0, 0, 0}
    };
    roundRobinScheduling(p, MAX, QUANTUM);
    displayResults(p, MAX);
    return 0;
}

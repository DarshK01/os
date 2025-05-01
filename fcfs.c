#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int ct;         // Completion Time
};

void calculateTimes(struct Process proc[], int n) {
    // Sort processes based on arrival time
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                // Swap processes
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // Calculate completion time for each process
    proc[0].ct = proc[0].at + proc[0].bt; // First process completes after its burst time
    for (int i = 1; i < n; i++) {
        proc[i].ct = proc[i - 1].ct + proc[i].bt;
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct - proc[i].at;  // Turnaround time = Completion time - Arrival time
        proc[i].wt = proc[i].tat - proc[i].bt;  // Waiting time = Turnaround time - Burst time
    }
}

void displayResults(struct Process proc[], int n) {
    // Sorting to display in original order (Process 1, Process 2, Process 3)
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].pid > proc[j].pid) {
                // Swap processes
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // Display the results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, proc[i].at, proc[i].bt, 
               proc[i].ct, proc[i].tat, proc[i].wt);
    }

    // Calculate and display average times
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
}

int main() {
    int n = 3;

    // Define processes with arrival time and burst time
    struct Process proc[] = {
        {1, 5, 2, 0, 0, 0},   // Process 1
        {2, 3, 0, 0, 0, 0},   // Process 2
        {3, 4, 4, 0, 0, 0}    // Process 3
    };

    // Calculate times
    calculateTimes(proc, n);

    // Display the results
    displayResults(proc, n);

    return 0;
}

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

    // Initialize variables
    int completed = 0, currentTime = 0, i;
    int shortestJobIndex;

    while (completed < n) {
        // Find the process with the shortest burst time that has arrived and not completed
        shortestJobIndex = -1;
        int minBurstTime = 9999;

        for (i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && proc[i].ct == 0 && proc[i].bt < minBurstTime) {
                minBurstTime = proc[i].bt;
                shortestJobIndex = i;
            }
        }

        if (shortestJobIndex != -1) {
            // Execute the process with the shortest burst time
            currentTime += proc[shortestJobIndex].bt;
            proc[shortestJobIndex].ct = currentTime;  // Completion time
            completed++;  // Increment the completed process count
        } else {
            // If no process is ready, increment the current time
            currentTime++;
        }
    }

    // Calculate turnaround time and waiting time
    for (i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct - proc[i].at;  // Turnaround time = Completion time - Arrival time
        proc[i].wt = proc[i].tat - proc[i].bt;  // Waiting time = Turnaround time - Burst time
    }
}

void displayResults(struct Process proc[], int n) {
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
    int n = 4;

    // Define processes with arrival time and burst time
    struct Process proc[] = {
        {1, 3, 1, 0, 0, 0},  // Process 1
        {2, 4, 2, 0, 0, 0},  // Process 2
        {3, 2, 14, 0, 0, 0}, // Process 3
        {4, 4, 14, 0, 0, 0}  // Process 4 (Assuming arrival time 14)
    };

    // Calculate times
    calculateTimes(proc, n);

    // Display the results
    displayResults(proc, n);

    return 0;
}

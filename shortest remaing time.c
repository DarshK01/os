#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int remaining_bt; // Remaining Burst Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int ct;         // Completion Time
};

void calculateTimes(struct Process proc[], int n) {
    int time = 0, completed = 0, min_index;
    int min_remaining_time = 9999;
    int all_done = 0;

    while (completed < n) {
        min_remaining_time = 9999;
        min_index = -1;

        // Find process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].remaining_bt > 0 && proc[i].remaining_bt < min_remaining_time) {
                min_remaining_time = proc[i].remaining_bt;
                min_index = i;
            }
        }

        if (min_index != -1) {
            proc[min_index].remaining_bt--; // Execute the process for one unit of time
            time++; // Increase time by 1 unit

            // If process completes
            if (proc[min_index].remaining_bt == 0) {
                proc[min_index].ct = time; // Set completion time
                proc[min_index].tat = proc[min_index].ct - proc[min_index].at; // Turnaround time
                proc[min_index].wt = proc[min_index].tat - proc[min_index].bt; // Waiting time
                completed++; // Process completed
            }
        } else {
            time++; // If no process is ready to execute, increment time
        }
    }
}

void displayResults(struct Process proc[], int n) {
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
        {1, 6, 0, 6, 0, 0, 0},  // Process 1
        {2, 3, 1, 3, 0, 0, 0},  // Process 2
        {3, 7, 2, 7, 0, 0, 0}   // Process 3
    };

    // Calculate times
    calculateTimes(proc, n);

    // Display the results
    displayResults(proc, n);

    return 0;
}

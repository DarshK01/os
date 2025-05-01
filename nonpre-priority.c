#include <stdio.h> 

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int priority;   // Priority (higher value means higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int ct;         // Completion Time
    int rt;         // Remaining Time (for simulation purposes)
};
void findWaitingTime(struct Process proc[], int n) {
    // Waiting time is computed after all processes have completed their execution
    for (int i = 0; i < n; i++) {
        proc[i].wt = proc[i].tat - proc[i].bt;}
}
void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct - proc[i].at;
    }
}
void priorityScheduling(struct Process proc[], int n) {
    struct Process temp;
    int completed = 0, currentTime = 0;

    // Sort the processes based on arrival time and priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at || 
                (proc[i].at == proc[j].at && proc[i].priority < proc[j].priority)) {
                // Swap the processes
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    while (completed < n) {
        int idx = -1;
        int highestPriority = -1;
        // Find the process with the highest priority that has arrived and not yet completed
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && proc[i].ct == 0) {  // Process has arrived and not completed
                if (proc[i].priority > highestPriority) {
                    highestPriority = proc[i].priority;
                    idx = i;
                }
            }
        }
        if (idx != -1) {
            // Update the current time and completion time for the selected process
            currentTime += proc[idx].bt;
            proc[idx].ct = currentTime;
            completed++;  // Increment completed process count
        } else {
            currentTime++;  // If no process can be executed, increment current time
        }
    }
    // Calculate waiting and turnaround times after completion
    findTurnAroundTime(proc, n);
    findWaitingTime(proc, n);

    // Display process details
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].priority, proc[i].wt, proc[i].tat, proc[i].ct);
    }
    // Calculate and display average times
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);}
int main() {
    int n = 5;
    struct Process proc[] = {
        {1, 4, 0, 2, 0, 0, 0},   // Process 1
        {2, 3, 1, 3, 0, 0, 0},   // Process 2
        {3, 1, 2, 4, 0, 0, 0},   // Process 3
        {4, 5, 3, 5, 0, 0, 0},   // Process 4
        {5, 2, 4, 5, 0, 0, 0}    // Process 5
    };
    // Run the priority scheduling
    priorityScheduling(proc, n);
    return 0;
}

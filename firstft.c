#include <stdio.h>

// Function to allocate memory to blocks as per First Fit algorithm
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    // Initially, no block is assigned to any process
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
  
    // Pick each process and find a suitable block
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to the ith process
                allocation[i] = j;
                
                // Reduce available memory in this block
                blockSize[j] -= processSize[i];
                
                break; // Move to the next process
            }
        }
    }

    // Print the allocation results
    printf("\n%-12s %-15s %-10s\n", "Process No.", "Process Size", "Block No.");
    for (int i = 0; i < n; i++) {
        printf("%-12d %-15d ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%-10d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Driver code
int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, m, processSize, n);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#define P 5 
#define R 4 
void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}
bool isSafe(int available[], int allocation[P][R], int need[P][R], int safeSequence[]) {
    int work[R], finish[P] = {0};
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}
bool canGrantRequest(int available[], int allocation[P][R], int need[P][R], int process, int request[]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }
    int tempAvailable[R], tempAllocation[P][R], tempNeed[P][R];
    for (int i = 0; i < R; i++) {
        tempAvailable[i] = available[i] - request[i];
    }
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            tempAllocation[i][j] = allocation[i][j];
            tempNeed[i][j] = need[i][j];
        }
    }
    for (int i = 0; i < R; i++) {
        tempAllocation[process][i] += request[i];
        tempNeed[process][i] -= request[i];
    }
    int safeSequence[P];
    return isSafe(tempAvailable, tempAllocation, tempNeed, safeSequence);
}
int main() {
    int available[R] = {2, 1, 0, 0}; 
    int max[P][R] = {
        {0, 0, 1, 2},  
        {2, 7, 5, 0},  
        {6, 6, 5, 6},  
        {4, 3, 5, 6},  
        {0, 6, 5, 2}   
    };
    int allocation[P][R] = {
        {0, 0, 1, 2},  
        {2, 0, 0, 0},  
        {0, 0, 3, 4},  
        {2, 3, 5, 4}, 
        {0, 3, 3, 2}   
    };
    int need[P][R];
    calculateNeed(need, max, allocation);
    int safeSequence[P];
    if (isSafe(available, allocation, need, safeSequence)) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }
    int request[R] = {0, 1, 0, 0}; 
    int process = 2;  
    if (canGrantRequest(available, allocation, need, process, request)) {
        printf("The request can be granted immediately.\n");
    } else {
        printf("The request cannot be granted immediately.\n");
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id, at, bt, ct, wt, tat, rt, st, remaining_bt;
} Process;
void calculate_averages(Process processes[], int n, float *avg_waiting, float *avg_turnaround, float *avg_response) {
    int total_wt = 0, total_tat = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
        total_rt += processes[i].rt;
    }
    *avg_waiting = (float)total_wt / n;
    *avg_turnaround = (float)total_tat / n;
    *avg_response = (float)total_rt / n;
}
void fcfs_scheduling(Process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].at) {
            current_time = processes[i].at;
        }
        processes[i].st = current_time;
        processes[i].ct = current_time + processes[i].bt;
        processes[i].wt = processes[i].st - processes[i].at;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].rt = processes[i].wt;
        current_time = processes[i].ct;
    }
    printf("FCFS Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d [%d-%d] ", processes[i].id, processes[i].st, processes[i].ct);
    }
    printf("\n");
    float avg_waiting, avg_turnaround, avg_response;
    calculate_averages(processes, n, &avg_waiting, &avg_turnaround, &avg_response);  
    printf("\nAverage WT: %.2f\tAverage TAT: %.2f\tAverage RT: %.2f\n", avg_waiting, avg_turnaround, avg_response);
}
void rr_scheduling(Process processes[], int n, int time_quantum) {
    int current_time = 0, completed = 0;
    for (int i = 0; i < n; i++) {
        processes[i].remaining_bt = processes[i].bt;
    }
    printf("Round Robin Scheduling Gantt Chart:\n");
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_bt > 0) {
                if (processes[i].remaining_bt == processes[i].bt) {
                    processes[i].st = (current_time > processes[i].at) ? current_time : processes[i].at;
                }
                int execution_time = (processes[i].remaining_bt > time_quantum) ? time_quantum : processes[i].remaining_bt;
                printf("P%d [%d-%d] ", processes[i].id, current_time, current_time + execution_time);
                processes[i].remaining_bt -= execution_time;
                current_time += execution_time;
                if (processes[i].remaining_bt == 0) {
                    processes[i].ct = current_time;
                    processes[i].wt = processes[i].ct - processes[i].at - processes[i].bt;
                    processes[i].tat = processes[i].ct - processes[i].at;
                    processes[i].rt = processes[i].st - processes[i].at;
                    completed++;
                }
            }
        }
    }
    printf("\n");
    float avg_waiting, avg_turnaround, avg_response;
    calculate_averages(processes, n, &avg_waiting, &avg_turnaround, &avg_response);
    printf("\nAverage WT: %.2f\tAverage TAT: %.2f\tAverage RT: %.2f\n", avg_waiting, avg_turnaround, avg_response);
}
int main() {
    int n, choice, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Number of processes must be greater than zero!\n");
        return 1;
    }
    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        if (processes[i].at < 0 || processes[i].bt <= 0) {
            printf("Invalid input! Arrival time must be >= 0 and burst time must be > 0.\n");
            return 1;
        }
    }
    do {
        printf("\nChoose Scheduling Algorithm:\n");
        printf("1. FCFS (First Come First Served)\n");
        printf("2. Round Robin (RR)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: fcfs_scheduling(processes, n); break;                
            case 2:
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &time_quantum);
                if (time_quantum <= 0) {
                    printf("Time quantum must be greater than zero!\n");
                } else {
                    rr_scheduling(processes, n, time_quantum);
                }
                break;
            case 3: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
                
        }
    } while (choice != 3);
    return 0;
}

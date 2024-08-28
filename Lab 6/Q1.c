#include <stdio.h>
#include <stdlib.h>  // For malloc, free, etc.

struct Process {
    char p_name;
    int arrival;
    int burst;
    int priority;
};

int compare(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;

    // Compare by arrival time
    return (processA->arrival == processB->arrival? processA->burst - processB->burst :processA->arrival - processB->arrival);
}

int max(int a , int b){
	return (a > b ? a : b);
}

// Function to display a Process
void display(struct Process process) {
    printf("Process %c: Arrival: %d; Burst: %d; Priority: %d\n", 
           process.p_name, process.arrival, process.burst, process.priority);
}

// Function to check if all processes are completed
int allCompleted(struct Process processes[], int size) {
    for (int i = 0; i < size; i++) {
        if (processes[i].burst > 0) {
            return 0; // Not all processes are completed
        }
    }
    return 1; // All processes are completed
}

// Function to determine which processes can start at a given time
int* canStart(struct Process processes[], int size, int timer) {
    int* can_start = (int *)malloc(size * sizeof(int));
    if (can_start == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit with an error code
    }

    for (int i = 0; i < size; i++) {
        if (processes[i].arrival == timer && processes[i].burst > 0) {
            can_start[i] = 1;
        } else {
            can_start[i] = 0;
        }
    }
    return can_start;
}

// Function to perform Round Robin scheduling
void round_robin(struct Process processes[], int size, int tq) {
    int* completed = (int *)malloc(size * sizeof(int));
    if (completed == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit with an error code
    }

    for (int i = 0; i < size; i++) {
        completed[i] = 0;
    }

    int timer = 0;
    while (!allCompleted(processes, size)) {
        int* can_start = canStart(processes, size, timer);

        for (int i = 0; i < size; i++) {
            if (can_start[i] == 1 && processes[i].burst > 0) {
                printf("Process %c: AT = %d ; BT = %d\n", processes[i].p_name, processes[i].arrival, processes[i].burst);

                if (processes[i].burst <= tq) {
                    processes[i].burst = 0;
                	completed[i] = 1;
                } else {
                    processes[i].burst -= tq;
                }
                // Update the timer for the process
                processes[i].arrival += tq;

            }
        }

        free(can_start); // Free the dynamically allocated memory for can_start
    }

    free(completed); // Free the dynamically allocated memory for completed
}

void FCFS(struct Process process[] , int size){
	qsort(process, size , sizeof(struct Process), compare);
	int timer = 0;
	for(int i = 0 ; i < size ; i++){
		printf("start : %d ",max(timer,process[i].arrival));
		printf("process : %c ",process[i].p_name);
		printf("end : %d \n", max(timer,process[i].arrival)+process[i].burst);
		timer = max(timer,process[i].arrival)+process[i].burst;
	}

}

int main() {
    // Define and initialize the Process array
    struct Process processes[] = {
        {'A', 21, 3, 0}, 
        {'B', 2, 1, 0}, 
        {'C', 50, 14, 0}, 
        {'D', 80, 5, 0},
        {'E',21,2,0}
    };
    int size = sizeof(processes) / sizeof(processes[0]);

    int choice;
    printf("MENU\n1. Preemptive-SJF \n2. Round Robin\n3. Nonpreemptive-SJF\n4. FCFS\n");
    printf("Enter your choice here: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Implement Preemptive-SJF here
            break;
        case 2:
            round_robin(processes, size, 2);
            break;
        case 3:
            // Implement Nonpreemptive-SJF here
            break;
        case 4:
        	FCFS(processes,size);
        	break;
        default:
            printf("Invalid Choice\n");
    }

    return 0;
}

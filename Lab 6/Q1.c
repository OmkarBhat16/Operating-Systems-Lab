#include <stdio.h>
#include <stdlib.h>  // For malloc, free, etc.

struct Process {
    char p_name;
    int arrival;
    int burst;
    int priority;
};

int compare_FCFS(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;

    // Compare by arrival time
    return (processA->arrival == processB->arrival? processA->burst - processB->burst :processA->arrival - processB->arrival);
}

int compare_np_SJF(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;

    // Compare by arrival time
    return (processA->burst == processB->burst? processA->arrival - processB->arrival :processA->burst - processB->burst);
}

int compare_p_SJF(const void *a, const void *b) {
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;

    // Compare by arrival time
    return (processA->arrival == processB->arrival ? processA->burst - processB->burst : processA->arrival - processB-> arrival);
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

// Function to perform Round Robin scheduling
void round_robin(struct Process processes[], int size, int tq) {
    int timer = 0;
    while(!allCompleted(processes, size)){
        for(int i = 0 ; i < size ; i++){
            if(processes[i].arrival ==timer){
                display(processes[i]);
                if(processes[i].burst <= tq){
                    processes[i].burst = 0;
                } else {
                    processes[i].burst -= tq;
                    processes[i].arrival += tq;
                }
            }
        }
        timer++;
    }
}

void FCFS(struct Process process[] , int size){
	qsort(process, size , sizeof(struct Process), compare_FCFS);
	int timer = 0;
	for(int i = 0 ; i < size ; i++){
		printf("start : %d ",max(timer,process[i].arrival));
		printf("process : %c ",process[i].p_name);
		printf("end : %d \n", max(timer,process[i].arrival)+process[i].burst);
		timer = max(timer,process[i].arrival)+process[i].burst;
	}
}

void  np_SJF(struct Process process[], int size){
    qsort(process, size , sizeof(struct Process), compare_np_SJF);
    int timer = 0;
    while(!allCompleted(process, size)){
        for(int i = 0 ; i < size ; i++){
            if(process[i].arrival == timer){
                display(process[i]);
            }
        }
        timer++;
    }
}

void p_SJF(struct Process process[], int size){
    qsort(process, size , sizeof(struct Process), compare_p_SJF);
    printf("sorted process : \n");

    for(int i = 0 ; i < size ; i++){
        display(process[i]);
    }
    printf("\n");
    int timer = 0, cur = 0;
    // while(!allCompleted(process, size)){
    //     for(int i = 0 ; i < size ; i++){
    //         if(process[i].arrival <= process[cur].arrival && process[i].burst < process[cur].burst){
    //             display(process[cur]);
    //             if(process[cur].burst <= timer){
    //                 process[cur].burst = 0;
    //             } else {
    //                 process[cur].burst -= timer;
    //             }
    //             cur = i;
    //         } else {
    //             display(process[cur]);
    //             if(process[cur].burst <= timer){
    //                 process[cur].burst = 0;
    //             } else {
    //                 process[cur].burst -= 1;
    //             }
    //         }
    //     }
    //     timer++;
    // }
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
            p_SJF(processes, size);
            break;
        case 2:
            round_robin(processes, size, 2);
            break;
        case 3:
            // Implement Nonpreemptive-SJF here
            np_SJF(processes, size);
            break;
        case 4:
        	FCFS(processes,size);
        	break;
        default:
            printf("Invalid Choice\n");
    }

    return 0;
}

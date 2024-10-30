#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf(int procs[], int size, int head);
void scan(int procs[], int size, int head, int dir);
void c_scan(int procs[], int size, int head);
void c_look(int procs[], int size, int head, int dir);
int cmp(const void* a, const void* b);
void display(int procs[], int size);
void initialize_array(int procs[], int size);


int main(){
	int size = 0;
	printf("Enter number of processes : ");
	scanf("%d",&size);

	int procs[size];

	for(int i = 0; i < size ; i++){
		printf("Enter value of process %d (including head) : ",i);
		scanf("%d",&procs[i]);
	}
	qsort(procs,size,sizeof(int),cmp);

	int head;
	printf("Enter starting head value : ");
	scanf("%d",&head);

	char menu[] = "MENU :\n1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\nEnter Option : ";
	printf("%s",menu);
	int choice = -1, dir = -1;
	scanf("%d",&choice);
	switch(choice){
	case 1:
		sstf(procs,size,head);
		break;
	case 2: 
		printf("Enter direction ( 0 : left , 1 : right ) : ");
		scanf("%d",&dir);
		scan(procs,size,head,dir);
		break;
	case 3:
		c_scan(procs,size,head);
		break;
	case 4:
		printf("Enter direction ( 0 : left , 1 : right ) : ");
		scanf("%d",&dir);
		c_look(procs,size,head,dir);
		break;
	default:
		printf("Invalid choice!\n");
	}

	return 0;
}

int cmp(const void* a, const void* b){
	return *(int *)a > *(int *)b;
}

void display(int procs[], int size){
	for(int i = 0; i < size; i++){
		printf("%d ",procs[i]);
	}
	printf("\n");
}

void initialize_array(int procs[], int size){
	for(int i = 0; i < size; i++)
		procs[i] = 0;
}


void sstf(int procs[], int size, int head) {
    // qsort(procs, size, sizeof(int), cmp);
    int flag[size];
    initialize_array(flag, size);
    int left, right, start = 0;

    for (int i = 1; i < size; i++) {
        if (procs[i] == head) {
            start = i;
            break;
        }
    }

    left = start - 1;
    right = start;

    if (left < 0) {
        printf("Starting at %d\n", head);
        display(procs, size);
        return;
    }
    if (right >= size) {
        printf("Starting at %d\n", head);
        for (int i = size - 1; i >= 0; i--) {
            printf("%d ", procs[i]);
        }
        printf("\n");
        return;
    }

    printf("Starting at %d\n", head);
    while(left >= 0 && right < size){
    	int leftDiff = head - procs[left];
    	int rightDiff = procs[right] - head;
    	if(leftDiff < rightDiff){
    		printf("%d to %d\n", head, procs[left]);
    		head = procs[left--];
    	} else {
    		printf("%d to %d\n", head , procs[right]);
    		head = procs[right++];
    	}
    }

    if(left < 0){
    	while(right < size){
    		printf("%d to %d\n", head , procs[right]);
    		head = procs[right++];
    	}
    } 
    if(right >= size){
    	while(left >= 0){
    		printf("%d to %d\n", head , procs[left]);
    		head = procs[left--];
    	}
    }    
}

void scan(int procs[], int size, int head, int dir){
	// qsort(procs,size,sizeof(int),cmp);
	int start = 0;
	for (int i = 1; i < size; i++) {
        if (procs[i] == head) {
            start = i;
            break;
        }
    }
	if(head - procs[0] < procs[size-1] - head){
		printf("Starts from %d\n",head);
		int ptr = start-1, last = 0;
		while(ptr >= 0){
			printf("%d to %d\n",procs[ptr+1], procs[ptr]);
			last = ptr;
			ptr--;
		}
		ptr = start + 1;
		while(ptr < size){
			printf("%d to %d\n",procs[last], procs[ptr]);
			last = ptr;
			ptr++;
		}
	} else {
		printf("Starts from %d\n",head);
		int ptr = start+1, last = 0;
		while(ptr < size){
			printf("%d to %d\n",procs[last], procs[ptr]);
			last = ptr;
			ptr++;
		}
		
		ptr = start - 1;
		while(ptr >= 0){
			printf("%d to %d\n",procs[last], procs[ptr]);
			last = ptr;
			ptr--;
		}
	}
}

// ADD traversal to 0 and upper end of cylinder
void c_scan(int procs[], int size, int head){
	int start = 0;
	for (int i = 1; i < size; i++) {
        if (procs[i] == head) {
            start = i;
            break;
        }
    }

    int completed = 0;
	printf("Starts from %d\n",head);
    while(1){
    	if(head - procs[0] < procs[size-1] - head){
    		while(completed < size){
	    		printf("%d to %d\n",procs[start],procs[(start-1 + size)%size]);
	    		completed++;
	    		start--;
    			start = (start+size)%size;
    		}
    	} else {
    		while(completed < size){
	    		printf("%d to %d\n",procs[start],procs[(start+1)%size]);
	    		completed++;
	    		start++;
    			start = (start+size)%size;
    		}
    	}
    }
}

void c_look(int procs[], int size, int head, int dir){
	int start = 0;
	for (int i = 1; i < size; i++) {
        if (procs[i] == head) {
            start = i;
            break;
        }
    }

    int completed = 0;
	printf("Starts from %d\n",head);
    while(1){
    	if(head - procs[0] < procs[size-1] - head){
    		while(completed < size){
	    		printf("%d to %d\n",procs[start],procs[(start-1 + size)%size]);
	    		completed++;
	    		start--;
    			start = (start+size)%size;
    		}
    	} else {
    		while(completed < size){
	    		printf("%d to %d\n",procs[start],procs[(start+1)%size]);
	    		completed++;
	    		start++;
    			start = (start+size)%size;
    		}
    	}
    }
}

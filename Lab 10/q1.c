#include <stdio.h>

void FIFO(int table[], int n , int pages[], int m);
void Optimal(int table[], int n , int pages[], int m);
void LRU(int table[], int n , int pages[], int m);
void copyArray(int dest[], int src[], int n);
int pageHit(int table[], int key, int n);
int findOptimal(int table[], int n, int pages[], int m, int idx);

void printTable(int table[], int n){
	for(int i = 0; i < n ; i++)
		printf("%d ",table[i]);
	printf("\n");
}

int main(){
	int n;
	printf("Enter size of table : ");
	scanf("%d",&n);

	int table[n];

	for(int i = 0; i < n; i++)
		table[i] = -1; 

	int m;
	printf("Enter number of processes : ");
	scanf("%d",&m);

	int pages[14] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};

	// for(int i = 0 ; i < m ; i++){
	// 	printf("Enter page number : ");
	// 	scanf("%d",&pages[i]);		
	// }



	int f_table[n];

	// copyArray(f_table, table, n);
	// FIFO(f_table,n,pages,m);

	copyArray(f_table, table, n);
	Optimal(f_table,n,pages,m);

	// copyArray(f_table, table, n);
	// LRU(f_table,n,pages,m);

	return 0;
}

int pageHit(int table[], int key, int n){
	for(int i = 0; i < n ; i++){
		if(table[i] == key)
			return 1;
	}	
	return 0;
}


void copyArray(int dest[], int src[], int n){
	for(int i = 0; i < n ; i++){
		dest[i] = src[i];
	}
}

int findOptimal(int table[], int n, int pages[], int m, int idx){
	for(int i = 0; i < n; i++){
		if(table[i] == -1)
			return i;
	}

	int swapTable[n];
    for(int i = 0; i < n ; i++){
        swapTable[i] = -1;
    }
    
	for(int i = 0; i < n ; i++){
		for(int j = idx+1; j < m; j++){
			if(table[i] == pages[j]){
                swapTable[i] = idx;
               	break;
			}
		}		
	}
	// printf("\n");
	// printTable(swapTable,n);
	int maxDist = -1;
	for(int i = 0; i < n; i++){
	    if(swapTable[i] == -1)
	        return i;
        
        maxDist = maxDist < swapTable[i] ? swapTable[i] : maxDist;
	}
	
	return maxDist != -1 ? maxDist : 0;
}


void FIFO(int table[], int n , int pages[], int m){
	int idx = 0;
	for(int i = 0; i < m ; i++){
		if(!pageHit(table,pages[i],n)){
			printf("Page Fault : %d replaces %d\t",pages[i],table[idx%n]);
			table[(idx)%n] = pages[i];
			printTable(table,n);
			idx++;
		} else {
			printf("Page Hit : %d found in table\t",pages[i]);
			printTable(table,n);
		}
	}
}



void Optimal(int table[], int n , int pages[], int m){
	int idx = 0;
	for(int i = 0; i < m ; i++){
		printf("%d\t",i);
		if(!pageHit(table,pages[i],n)){
			int replaceIdx = findOptimal(table,n,pages,m,idx);
			printf("Page Fault : %d replaces %d at %d\t",pages[i],table[replaceIdx],replaceIdx);
			table[replaceIdx] = pages[i];
			printTable(table,n);
		} else {
			printf("Page Hit : %d found in table\t",pages[i]);
			printTable(table,n);
		}
	}
}

void LRU(int table[], int n , int pages[], int m);
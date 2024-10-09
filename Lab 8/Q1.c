#include<stdio.h>

int canComplete(int available[3], int need[5][3], int row){
    int i, j;
    for(i = 0; i < 3; i++){
        if(available[i] < need[row][i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int total[3] = {10,5,7};
    int available[3] = {3, 3, 2};
    int max[5][3] = {{7, 5, 3},
                        {3, 2, 2},
                        {9, 0, 2},
                        {2, 2, 2},
                        {4, 3, 3}};

    int allocated[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int need[5][3];

    for(int i = 0 ; i < 5; i++){
        for(int j = 0; j < 3; j++){
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    int order[5] = {0,0,0,0,0};
    int finished = 0;
    int flags[5] = {0,0,0,0,0};
    int i = 0, k = 0;
    while(finished < 5){
        if(flags[i]==0 && canComplete(available, need, i))
        {
            for(int j = 0; j < 3; j++){
                available[j] += allocated[i][j];
            }
            flags[i] = 1;
            order[k++] = i;
            finished++;
        }
        i = (i+1)%5;
    }


    for(int i = 0; i < 5; i++){
        printf("%d ", order[i]);
    }

    return 0;
}

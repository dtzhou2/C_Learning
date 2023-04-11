#include <stdio.h>
#include <stdlib.h>
int maxProfit(int prices[], int size){
    int min = prices[0];
    int max = prices[0];

    for(int i=0; i<size; i++){
        if(prices[i] < min) min = prices[i];
        if(prices[i] > max) max = prices[i];
    }
    return max-min;
}

void swap(char *a, char *b){
    char temp = *a;

    *a = *b;
    *b = temp;
}

void permutation(char *s, int left, int right){
    if(left == right) printf("%s\n", s);
    else{
        for(int i=left; i<=right; i++){
            swap(&(s[left]), &(s[i]));

            permutation(s, left+1, right);

            swap(&(s[left]), &(s[i]));

        }
    }

}

int binSearch(int arr[], int start, int end, int item){
    if(start >= end) return -1;
    if(start == end) return start;
    
    int mid = (start+end)/2;
    if(arr[mid] == item) return mid;
    if(arr[mid] > item) return binSearch(arr, start, mid, item);
    if(arr[mid] < item) return binSearch(arr, mid, end, item);

}

int RemoveDuplicates(int *arr, int n){
    int lastUnique;

    for(int i=0; i<n; i++){
        if(arr[i] != arr[lastUnique]){
            lastUnique ++;
            arr[lastUnique] = arr[i]
        }
    }

    return lastUnique;
}

int min(int a, int b){
    if (a>b) return b;
    return a;
}

int min_path_sum(int grid[][], int m, int n, int i, int j){
    if(i == 0  && j == 0) return grid[i][j];
    if(i>=m || i<0 || j>=n || j<0) return __INT_MAX__;

    int mps_t = min_path_sum(grid, m, n, i-1, j);
    int mps_l = min_path_sum(grid, m, n, i, j-1);

    return grid[i][j] + min(mps_t, mps_l);

}

int main(void) {
    int arr[6] = {2,7,3,1,2,8};
    char a = 'c';
    char b = 'd';
    char str[] = "DEF";

    printf("Max profit is: %d \n", maxProfit(arr, 6));
    printf("Char A is: %c Char B is: %c \n", a, b);
    swap(&a, &b);
    printf("After Swap, Char A is: %c Char B is: %c \n", a, b);

    permutation(str, 0, 2);

    int arr1[5] = {1,2,3,4,5};
    int* arr2[5];

    for(int i=0; i<5; i++){
        arr2[i] = arr1+i;
    }

    for(int i=0; i<5; i++){
        printf("%p\n", arr2[i]);
    }

    int arr3[7] = {1,2,3,4,5,6,7};
    printf("Return Value is: %d \n", binSearch(arr3, 0, 6, 5));

    int grid1[3][3]={1, 2, 3, 3, 4, 1, 2, 5, 1};
    int m = 3;
    int n = 3;

    int sum = min_path_sum(grid1, m, n, m-1, n-1);
    printf("min path sum of grid1 is %d \n", sum);

    int grid2[3][4]={1, 3, 2, 1, 1, 2, 1, 2, 3, 2, 1, 1};
    m = 3;
    n = 4;

    sum = min_path_sum(grid2, m, n, m-1, n-1);
    printf("min path sum of grid2 is %d \n", sum);
}
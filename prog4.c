
#include <stdio.h>

void print_semiprimes(int a, int b);
int is_prime(int number);

int main(void){

    int a;
    int b;

    // Grab Input Number A
    printf("Enter the Start of the Range: ");
    scanf("%d", &a);

    // Grab Input Number B
    printf("Enter the End of the Range: ");
    scanf("%d", &b);

    print_semiprimes(a, b);

    return 0;
}

void print_semiprimes(int a, int b){
    for (int n = a; n <= b; n++){
        for(int k = 2; k < n-1; k++){
            if ( n%k == 0 && is_prime(n/k) == 0 && is_prime(k) == 0){
                printf(" %d", n);
                break;
            }
        }
    }
}

int is_prime(int number){
    for (int i=2; i<number; i++){
        if(number%i==0) return 1;
    }
    return 0;
}
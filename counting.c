void increment(void) {
    static unsigned int counter = 0;
    counter ++;
    printf("%d\n", counter);
}

int main(void) {
    for(int i =0; i < 5; i++){
        increment();
    }
    return 0;
}
#include <stdio.h>
#include <stddef.h>

void swap(int*, int*);
int max(int a, int b);
int funnnnnnction(void);
void not_f(int (*func)(void));
int fun(void);
int gun(void);

union first_union {
    struct int_version{
        int type;
        int node_num
    } fi;
    struct unsigned_int_version{
        int type;
        unsigned int node_num;

    } fu;
    struct float_version{
        int type;
        float node_num;
    } ff;
} f, *f_p;

typedef struct my_struct {
    int c;
    char str[20];
    unsigned int j;
} my_struct;

int main(void) {
    int a = 21;
    int b = 17;

    //Function types and scopes
    swap(&a,&b);
    printf("main: a = %d, b=%d\n", a, b);

    //Basic Structure Shit
    my_struct structA;
    my_struct* structA_p = &structA;
    structA.c = 5;
    printf("StructA Value %d\n", structA_p->c);

    //Basic Union Shit 
    f_p = &f;
    f.fu.type = 0;
    f.fu.node_num=1;
    printf("F Value %d\n", f_p->fu.type);
    
    //Basic Floating point and Type Conversion Shit
    short si = 5; // 2^15 min size
    long dd = 8; // 2^31 min size
    char ci = 127; //2^7 max size 
    
    long se = (long)(si+dd);

    float ff = 12.35; //32 Bit Floating Point Number
    float fd = 43.3456; //64 Bit Floating Point Number
    long fl = 67.73485; //Long - Implementation varies by compiler
    //SIGNED INTEGER OVERFLOW IS ALWAYS A DEFECT

    //Basic Assignment Shit
    int j = 5; // lvalue = *j , rvalue = 5
    int e = 8; // lvalue = *e, rvalue = 8
    int max_of = max(j, e); // lvalue = function_designator: pointer-to-function returning type 
    int* p = &j-4;
    *(p+4) = e; // lvalue = *(p+4), rvalue = 8
    int z = ++e; //Increment and decrement operators can be prefix or postfix
    int y = --e; // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    int multiply = 5+8*4; // Due to OrderOfOperations(OOP) This expression is evaluated as 5+(8*4) !!!!NOT!!!!! (5+8)*4
    printf("Value of j is %d \n", j);
    printf("Value of max is %d \n", max_of);
    printf("Value of multiply is %d \n", multiply);

    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON POSTFIX INCREMENT/DECREMENT
    int sadf = 5;
    printf("Value of sadf %d \n", sadf++); //WHEN ++ IS POSTFIX IT RETURNS THE ORIGINAL VALUE BUT CHANGES THE VARIABLE
    printf("Value of sadf %d \n", sadf); //SEE HERE THE ORIGINAL VARIABLE IS NOW 6 BUT THE ++ RETURNS THE OLD VALUE 5

    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    //EXTREMELY IMPORTANT LESSON ON PREFIX INCREMENT/DECREMENT
    int asdf = 5;
    printf("Value of sadf %d \n", ++asdf); //WHEN ++ is prefix it returns the NEW CHANGED VARIABLE
    printf("Value of sadf %d \n", asdf); //SEE HERE THE ORIGINAL VARIABLE IS NOW 5 BUT THE ++ RETURNS THE NEW CHANGED VARIABLE 6

    //Operator Precedence Shit
    char abc[] = "hello";
    char* abc_p = abc;
    printf("Value of abc %c \n", *abc_p);
    char abc_p1 = ++*abc_p;
    // char abc_p2 = *abc_p++;
    printf("Value of abc %c \n", *abc_p);
    printf("Value of abc_p1 %c \n", abc_p1);
    // printf("Value of abc_p2 %c \n", abc_p2);

    //Order of evaluation shit
    printf("Value of max value %d \n", max(fun(), gun())); //WHEN ++ is prefix it returns the NEW CHANGED VARIABLE

    //Sequencing Shit
    int ii = 5;
    int jj = ii++; //This is a sequencing point
    int kk = ii++; // This is also a sequencing point

    printf("Result = %d\n", jj * kk);
    //printf("Result = %d\n", ++ii * ii++); // This is VERY BAD coding :D it has undefined behavior
                                          // Due to the fact that sequencing points are not defined

    //Operator Shit
    long long inter;
    size_t inter_size = sizeof inter; //Gets size of object in bytes
    size_t inter_size_bytes = sizeof(inter) * __CHAR_BIT__ ; //__CHAR_BIT__ represents number of bits in a byte
    
    printf("Result = %d\n", inter_size);
    printf("Result = %d\n", inter_size_bytes);

    //Logical Negation Operator
    int* null_p = NULL;
    short null_check = !null_p;
    
    printf("Is pointer value null = %d\n", null_check);

    //Multiplicative Operator
    int divisor = 23;
    int other_int = 4;
    int remainder = 0;

    printf("Value = %d\n", divisor/other_int);
    printf("Remainder = %d\n", divisor%other_int);

    //Shifting Time!!!!
    divisor = 0xFFFB;
    divisor << 2; //Left Shifts the bits by 2
    divisor >> 2; //Right Shifts the bits by 2

    printf("Remainder = %d\n", divisor);


    return 0;

}

void swap(int *pa, int *pb){
    int t = *pa;
    *pa = *pb;
    *pb = t;
}

int max(int a, int b ){
    if(a > b){
        return a;
    }
    else return b;
    swap(&a, &b);
}

//Trolly function invocation shit
int funnnnnnction(void){
    return 0;
}

void not_f(int (*func)(void)){ //You can pass in functions as arguments to other functions by using the pointer-to-function returning type 
    if (func()!=0) printf("g failed \n");
}

//Order of Evaluation Shit 

int glob;

int fun(void){
    return glob+10;
}

int gun(void){
    glob = 42;
    return glob;
}
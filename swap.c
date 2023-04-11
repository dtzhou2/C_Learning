#include <stdio.h>
#include <stddef.h>
#include <limits.h>

void swap(int*, int*);
int max(int a, int b);
int funnnnnnction(void);
void not_f(int (*func)(void));
int fun(void);
int gun(void);
int sum_m_elems(void);
int absolute_value(int a);
int m[2] = {1,2};

union first_union {
    struct int_version{
        int type;
        int node_num;
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

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct widget {
    int data;
    int *data_2;
    char name[255];
    float value;
} widget;

node *ppp;

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

    printf("SHIFT Operator = %d\n", divisor);

    //ANDing Time!!!
    divisor = 0xFFFB;
    divisor = divisor & 0x0000; // & operator returns the bitwise AND of two operators

    printf("AND Operator = %d\n", divisor);

    //ORing Time!!
    divisor = 0xFFFB;
    // divisor = divisor & 0x0000; // & operator returns the bitwise AND of two operators
    divisor = divisor ^ 0x0000; // ^ operator returns the bitwise XOR of two operators
    divisor = divisor | 0x0000; // | operator returns the bitwise inclusive OR of two operators

    printf("OR Operator = %d\n", divisor);

    //Short Circuiting and Logical Operators
    int* ptr = NULL;
    
    printf("Logical AND Operator %d\n", divisor && 0x0000);
    printf("Logical OR Operator %d\n", divisor || 0x0000); // Short Circuits to 1, not evaluating second operator
    // This is due to fact that first operator evaluates to !0 
    printf("Short Circuiting AND Operator %d\n", ptr && *ptr); // Short Circuits to 0, not evaluating second operator
    // This is due to the fact that the first operator evaluates to 0

    //Casts **DANGEROUS**
    int* divisor_ptr = &divisor;
    int cast_ptr = (int)divisor_ptr; //This is a terrible Cast

    printf("Uncast Pointer %d\n", *divisor_ptr); //This returns the correct dereferencing operator
    printf("Why casts can be dangerous Operator %d\n", cast_ptr); // This returns garbage because casting a pointer to an int doesnt work

    //Conditional Operator
    divisor = divisor || 0x000 ? 9 : 1; // Conditional operator. First operator before the ? denotes the conditional clause
    // Next operator before the : denotes value if True
    // Next operator denotes the value if False
    // In other words divisor = conditionalStatement ? valueifTrue : valueifFalse
    printf("Result of the conditional operator is %d\n", divisor);

    divisor = divisor < 4 ? 4 : 5;
    printf("Result of the conditional operator is %d\n", divisor);

    // a < b < c IS WRONG it evaluates to (a < b) < c which compares 0/1 (the result of a < b) to c
    // a < b == c < d IS WRONG. The equality operator evlauates LAST 
    // ptr_a < ptr_b is UNDEFINED BEHAVIOR DONT DO IT 

    //Compound Assignment Operators 
    divisor = 8;
    printf("Base value of divisor is %d\n", divisor);
    divisor += 1; // Changes the variable to the current variable added by 1
    printf("Result of the += assignment operator is %d\n", divisor);
    divisor -= 1; // Changes the variable to the current variable subtracted by 1
    printf("Result of the -= assignment operator is %d\n", divisor);
    divisor *= 2; // Changes the variable to the current variable multiplied by 2
    printf("Result of the *= assignment operator is %d\n", divisor);
    divisor /= 2; // Changes the variable to the current value divided by 2
    printf("Result of the /= assignment operator is %d\n", divisor);
    divisor %= 5; // Changes the variable to the current value modded by 5
    printf("Result of the %%= assignment operator is %d\n", divisor);
    divisor <<= 3; // Changes the variable to the current value left shifted 3 Places
    printf("Result of the <<= assignment operator is %d\n", divisor);
    divisor >>= 2; // Changes the variable to the current value right shifted 2 places
    printf("Result of the >>= assignment operator is %d\n", divisor);
    divisor |= 0x0007; // Changes the variable to the current value OR 0x0007
    printf("Result of the |= assignment operator is %d\n", divisor);
    divisor &= 0x000C; // Changes the variable to the current value AND x000C
    printf("Result of the &= assignment operator is %d\n", divisor);
    divisor ^= 0x0008; // Changes the value to the current value XOR x0008
    printf("Result of the ^= assignment operator is %d\n", divisor);

    //Too Far Pointer Shit
    printf("Result of the pointer summation is %d\n", sum_m_elems());

    //Switch Statement Shit
    divisor = 100;
    switch (divisor/10) {
        case 10: {
            printf("Hello \n");
            printf("Hi HI \n"); //This switch case acts the same as an if-else ladder except the condition statement has to be an int
            break; //Break statement prevents fall-through where it jumps to next switch case instead of quitting switch n  
        }

    }    


    // Why while statements can get trolly
    // for (ppp = head; ppp!= NULL; ppp->next) free(p)
    // This does not work because the ppp->next occurs after the free(p) so you are reading a freed variable, which is undefined behavior
    // Above loop translates to
    // ppp = head;
    // while (ppp != NULL){
    //     free(p);
    //     ppp = ppp->next;
    // }
    // Second Statement in for loop executes at end of loop
    goto JUMPPOINT;

    // Exercise for demonstrating how control flow works
    printf("Helllo"); // Jumppoint skips over this statement and moves over to next statement
    JUMPPOINT:
        printf("Return value %d\n", absolute_value(20));

    // Pointer Shittttt!!!!!
    widget *wid_p = malloc(sizeof(widget)); // malloc command allocates enough memory space to hold an object of the size passed in the arguments
    wid_p->data_2 = malloc(sizeof(int)*3); // By combining malloc with sizeof() we can allocate enough space to fit custom objects and pointers
    // MALLOC DOES NOT ZERO THE MEMORY
    wid_p->data_2 = calloc(3, sizeof(int)); // This statement is equivelent to malloc statement above it but CALLOC ZEROES THE MEMORY 
    // realloc(wid_p->data_2, 5); // This will grow the size of the array by 5 since realloc adds additional memory space to a pointer
    
    // Safe Realloc Code Here
    int *temp_point;
    if (temp_point = realloc(wid_p->data_2, 5) == NULL){ // If the realloc fails, the original address space defined by wid_p -> data_2
    // is not freed but is left unreadable, but the output of realloc is NULL
        free(wid_p->data_2); // By freeing wid_p->data_2 it guarantees that that memory space is not leaked
    }
    temp_point = wid_p->data_2;
    wid_p->data_2 = malloc(sizeof(int)); // Reallocates wid_p->data_2 guarantees that the class is still usable even though data is lost


    wid_p->data_2[0] = 5;
    wid_p->data = 4;

    printf("widget data object = %d", wid_p->data);
    free(wid_p->data_2); // wid_p->data2 can be considered a dangling pointer because the address it is pointing to has been freed
    wid_p->data_2 = NULL; //Clears dangling pointer by nullifying pointer vlaue 
    free(wid_p);
    wid_p = NULL;
    free(temp_point);
    temp_point = NULL;

    return 0;
}

// This code breaks when A = INT_MIN because twos complement means the negation is one greater than the positive range
// Added if statements to prevent that behavior
int absolute_value(int a){
    if ( a < 0 && a != INT_MIN){
        return -a;
    }
    if ( a == INT_MIN) return -1;
    return a;
}

int sum_m_elems(void){ 
    //This set of three statements counts as a compound statement since it is inside curly braces
    int *pi; int j =0;
    for(pi = &m[0]; pi < &m[2]; ++pi) j += *pi; //&m[2] Exists even though it doesnt point to an array element
    // This is defined behavior because it allows loops like this to easily increment through the array
    return j;
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
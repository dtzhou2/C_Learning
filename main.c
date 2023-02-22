#include <stdio.h>
#include <stddef.h>
#include <limits.h>

#define LOWER 0  /* Lower Limit of Table */
#define UPPER 300 /* Upper Limit */
#define STEP 20 /* Step Size */

// Defines allows us to do conditional preprocessing, shown below
/* 
    #ifdef IM_USING_OPENGL
        opengl(context, blah)
    #else
        directx(blah);
    #endif
*/
// Defines also allows us to abstract away magic constants to enhance readability
// Defines also allows us to define a magic value in just the source file and have 
// it be called by its defines everywhere else

int main(void){

    printf("(F)\t(C)\n");
    
    // float celsius, fahr;
    // int lower, upper, step;

    // lower = -100;
    // upper = 300;
    // step = 20;

    // celsius = lower;

    // Print Celsius to Farenheit
    // while (celsius <= upper) {
    //     fahr = ( celsius * (9/5) ) + 32;
    //     printf("%.2f\t%.2f\n", celsius, fahr);
    //     celsius = celsius + step;
    // }

    // Print Farenheit to Celsius
    // while (fahr <= upper) {
    //     // Always indent for while statements 
    //     celsius = 5 * (fahr - 32) / 9;
    //     printf("%d\t%d\n", fahr, celsius);
    //     fahr = fahr + step;
    //     /*
    //         %d prints as decimal integer
    //         %f prints as floating point
    //         %6.2f prints as floating point, at least 6 wide and 2 after decimal point
    //         %o for octal
    //         %x for hex
    //         %c for character
    //         $s for char string
    //         %% for % 
    //     */
    // }

    // Same Code just miniaturized by using a for loop
    float celsius  = 0;

    for (float fahr = 0; fahr < 300; fahr = fahr + 20){
        celsius = 5 * (fahr - 32) / 9 ;
        printf("%f\t%f\n", fahr, celsius);
    }

    // Basic GetChar / PutChar functionality allows us to create very powerufl programs
    // GetChar just reads one char from input stream, putcharm dumps that char into stdout
    // int c ; // We usse int variable here since EOF is too big to store in a char
    // If you think about how it works under the hood a char is just a super tiny int

    // Any assignment in C has an expression and a value, which is the value of the left-hand side
    // Any assignment can appear as part of a larger expression
    // IMPORTANT
    // c = getchar() != EOF IS EQUIVALENT TO c = (getchar() != EOF)
    // THIS MEANS C GETS SET TO 0 or 1 BASED ON GETCHAR() OUTPUT
    // printf("%d", c = getchar() != EOF);
    // printf("%x\n", EOF);
    // while((c = getchar()) != EOF){
    //     putchar(c);
    //     c = getchar();
    // }

    // int date;
    // printf("Enter a date in September 2020: ");
    // scanf("%d", &date);

    // switch(date%7){
    //     case 0:
    //         printf("9/%d/20 is a Monday", date);
    //         break;
    //     case 1:
    //         printf("9/%d/20 is a Tuesday", date);
    //         break;
    //     case 2:
    //         printf("9/%d/20 is a Wednesday", date);
    //         break;
    //     case 3:
    //         printf("9/%d/20 is a Thursday", date);
    //         break;
    //     case 4:
    //         printf("9/%d/20 is a Friday", date);
    //         break;
    //     case 5:
    //         printf("9/%d/20 is a Saturday", date);
    //         break;
    //     case 6:
    //         printf("9/%d/20 is a Sunday", date);
    //         break;
    //     default:
    //         printf("Invalid Date");
    //         break;

    // }


    // int sum = 0;
    // int num = 3;
    // double average;

    // printf("Enter how many numbers to input: ");
    // scanf("%d", &num);
    
    // printf("\n");

    // for (int i = 0; i < num ; i++){
    //     int temp = 0;
    //     scanf("%d", &temp);
    //     sum +=temp;

    // }
    // average = sum / num ; 

    // printf("The average of the numbers: %lf\n", average);

    // int num = -1;

    // while (num != 0 && (num > 10 || num < 0)){
    //     printf(" Enter the number of * to print out (1-10), enter 0 to exit: ");
    //     scanf("%d", &num);
    // }

    // long nc;

    // nc = 0;

    // while (getchar() != EOF)
    //     ++ nc;

    // printf("%ld\n", nc);

    // int c, n1;

    // int pchar;

    // n1 = 0 ;

    // Count the amount of line breaks in your input char
    // while((c = getchar()) != EOF)
    //     if (c == '\n')
    //         ++n1;
    // printf("%d\n", n1);

    // Write a program to count blanks, tabs, and newlines
    // while((c = getchar()) != EOF)
    //     if (c == '\n' || c == ' ' || c == '\t')
    //         ++n1;
    // printf("%d\n", n1);

    // Outputs the input string minus all the whitespace
    // while((c = getchar()) != EOF){
    //     if (c != pchar) {
    //         putchar(c);
    //         pchar = c;
    //     }
    // }



    return 0;
}
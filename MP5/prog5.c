#include <stdlib.h>
#include <stdio.h>

/* 
 * Your code is included as part of this file.
 */
#include "prog5.h"

/*

 * The functions that you must write are defined in the header file.

 * Blank function prototypes with explanatory headers are provided

 * in this file to help you get started.

 */

#include <stdio.h>

#include <stdlib.h>

#include "prog5.h"

/*

 * You will need to keep track of the solution code using file scope

 * variables as well as the guess number.

 */

static int guess_number;

static int solution1;

static int solution2;

static int solution3;

static int solution4;

/*

 * in_range --  This helper function is used by make_guess to determine if

 *              a number is in a specified range.

 * INPUTS: value -- the number to verify is in the range

 *         min -- the lower bound of the range (inclusive)

 *         max -- the upper bound of the range (inclusive)

 * RETURN VALUE: 1 if value is between min and max, inclusive

 *               0 otherwise

 */

int in_range(int value, int min, int max) {
    if(min <= value || value <= max) return 1;
    return 0;
}

/*

 * set_seed -- This function sets the seed value for pseudorandom

 * number generation based on the number the user types.

 * The input entered by the user is already stored in the string seed_str by the code in main.c.

 * This function should use the function sscanf to find the integer seed value from the

 * string seed_str, then initialize the random number generator by calling srand with the integer

 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.

 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed

 * OUTPUTS: none

 * RETURN VALUE: 0 if the given string is invalid (string contains anything

 *               other than a single integer), or 1 if string is valid (contains one integer)

 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"

 *               if string is invalid. Prints nothing if it is valid.

 */

int set_seed (const char seed_str[]){
    int seed_value = 0;
    char padding[250];

    if( sscanf( "%d  %s", seed_value, padding ) == 1) {
        srand(seed_value);
        return 1;
    }

    // Something went wrong / Invalid
    printf("Sorry Could Not Parse Your Input");
    return 0;

}

/*

 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.

 *               This function creates the four solution numbers using the approach

 *               described in the wiki specification (using rand())

 *               The four solution numbers should be stored in the static variables defined above.

 *               The values at the pointers should also be set to the solution numbers.

 *               The guess_number should be initialized to 1 (to indicate the first guess)

 * INPUTS: none

 * OUTPUTS: *one -- the first solution value (between 1 and 6)

 *          *two -- the second solution value (between 1 and 6)

 *          *three -- the third solution value (between 1 and 6)

 *          *four -- the fourth solution value (between 1 and 6)

 * RETURN VALUE: none

 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number

 */

void start_game (int* one, int* two, int* three, int* four) {
    solution1 = rand() % 5 + 1;
    solution2 = rand() % 5 + 1;
    solution3 = rand() % 5 + 1;
    solution4 = rand() % 5 + 1;
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;
    guess_number = 1;

    printf("Solutions: %d , %d , %d , %d", solution1, solution2, solution3, solution4);
}

/*

 * make_guess -- This function is called by main.c after the user types in a guess.

 *               The guess is stored in the string guess_str.

 *               The function must calculate the number of perfect and misplaced matches

 *               for a guess, given the solution recorded earlier by start_game

 *               The guess must be valid (contain only 4 integers, within the range 1-6). If it is valid

 *               the number of correct and incorrect matches should be printed, using the following format

 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"

 *               If valid, the guess_number should be incremented.

 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.

 *               For an invalid guess, the guess_number is not incremented.

 * INPUTS: guess_str -- a string consisting of the guess typed by the user

 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)

 *          *one -- the first guess value (between 1 and 6)

 *          *two -- the second guess value (between 1 and 6)

 *          *three -- the third guess value (between 1 and 6)

 *          *four -- the fourth color value (between 1 and 6)

 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four

 *               numbers between 1 and 6), or 0 if it is invalid

 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)

 *               or an error message (invalid guess)

 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)

 */

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four){

    int* w;
    int* x;
    int* y;
    int* z;
    char post[2];
    int low = 1;
    int imp_matches;
    int perf_matches;
    int o_pair;
    int t_pair;
    int th_pair;
    int f_pair;

    if(sscanf (guess_str, "%d %d %d %d %1s", w, x, y, z, post) != 4) {
        printf("make_guess: invalid guess\n");
        return 0;
    }

    if(in_range(*w, 1, 6) == 0  in_range(*x, 1, 6) || in_range(*y, 1, 6) == 0 || in_range(*z, 1, 6) == 0 ){
        printf("make_guess: invalid guess\n");
        return 0;
    }

    // Setting Values
    *one = w;
    *two = x;
    *three = y;
    *four = z;

    // Guess one check
    if ( w = solution1 ){
        perf_matches = perf_matches + 1;
        o_pair = 1;
    }
    else if ( w = solution2  && !t_pair ){
        imp_matches = imp_matches + 1;
        t_pair = 1;
    }
    else if ( w = solution3 && !th_pair ){
        imp_matches = imp_matches + 1;
        th_pair = 1;
    }
    else if ( w = solution4 && !f_pair ){
        imp_matches = imp_matches + 1;
        f_pair = 1;
    }

    // Guess Two Check
    if ( w = solution1 ){
        perf_matches = perf_matches + 1;
        o_pair = 1;
    }
    else if ( w = solution2  && !t_pair ){
        imp_matches = imp_matches + 1;
        t_pair = 1;
    }
    else if ( w = solution3 && !th_pair ){
        imp_matches = imp_matches + 1;
        th_pair = 1;
    }
    else if ( w = solution4 && !f_pair ){
        imp_matches = imp_matches + 1;
        f_pair = 1;
    }

    // Guess Three Check
    if ( w = solution1 ){
        perf_matches = perf_matches + 1;
        o_pair = 1;
    }
    else if ( w = solution2  && !t_pair ){
        imp_matches = imp_matches + 1;
        t_pair = 1;
    }
    else if ( w = solution3 && !th_pair ){
        imp_matches = imp_matches + 1;
        th_pair = 1;
    }
    else if ( w = solution4 && !f_pair ){
        imp_matches = imp_matches + 1;
        f_pair = 1;
    }

}


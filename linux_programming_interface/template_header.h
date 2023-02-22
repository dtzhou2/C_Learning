#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* Prevents accidental double inclusion */

#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /*Standard I/O Functions */
#include <stdlib.h> /* Prototypes of commonly used library functions */
                    /* plus EXIT_SUCCESS and EXIT_FAILURE functions */
#include <unistd.h> /* Prototypees for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */

#include "get_num.h" /* Declares our functions for handling numberic arguments */
                     /* (getInt(), getLong()) */

#include "error_functions.h" /* Declares our error-handling functions */

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif


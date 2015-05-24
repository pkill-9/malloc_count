/**
 *  Functions for recording calls to malloc and free.
 */


#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "memlog_functions.h"
#include "utils.h"


/***********************************************************/


PRIVATE size_t get_allocation_size (void *pointer);


/***********************************************************/


FILE *logfd;


/***********************************************************/


/**
 *  Log memory allocations, and print the details to a file in CSV format.
 */
    PUBLIC void *
log_malloc (const char *file, int line, const char *func, size_t bytes)
{
    bytes += sizeof (size_t);
    void *address = malloc (bytes);

    fprintf (logfd, "malloc,\"%s\",%d,\"%s\",%p,%d\n", file, line,
      func, address, bytes);

    /** store the size of the block in the first padding that we added for
     *  this exact purpose. */
    *(size_t *) address = bytes;

    return ((size_t *) address) + 1;
}


/***********************************************************/


/**
 *  Log calls to free.
 */
    PUBLIC void
log_free (const char *file, int line, const char *func, void *ptr)
{
    size_t size = get_allocation_size (ptr);
    ptr = (void *) (((size_t *) ptr) - 1);

    free (ptr);

    fprintf (logfd, "free,\"%s\",%d,\"%s\",%p,%d\n", file, line,
      func, ptr, size);
}


/***********************************************************/


/**
 *  When malloc is used to allocate a chunk of memory, the size of the
 *  chunk is stored as a 16 bit number immediately before the chunk that
 *  was allocated. Given a pointer, this function will find out the size
 *  of the allocated chunk.
 */
    PRIVATE size_t
get_allocation_size (void *pointer)
{
    return * (((size_t *) pointer) - 1);
}


/***********************************************************/


/**
 *  Initialise logging of calls to malloc and free. This function will
 *  open a log file to record output to.
 */
    PUBLIC void
open_memlog (const char *progname)
{
    logfd = fopen ("mem.log", "w");
    fprintf (logfd, "opcode,file,line,func,address,size\n");
}


/***********************************************************/


/**
 *  Closes the log file.
 */
    PUBLIC void
close_memlog (void)
{
    fclose (logfd);
}


/***********************************************************/

/** vim: set ts=4 sw=4 et : */

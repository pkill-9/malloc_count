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
log_malloc (const char *file, const char *line, const char *func, 
  size_t bytes)
{
    void *address = malloc (bytes);

    fprintf (logfd, "malloc,\"%s\",\"%s\",\"%s\",%p,%d\n", file, line,
      func, address, bytes);

    return address;
}


/***********************************************************/


/**
 *  Log calls to free.
 */
    PUBLIC void
log_free (const char *file, const char *line, const char *func, void *ptr)
{
    size_t size = get_allocation_size (ptr);

    free (ptr);

    fprintf (logfd, "free,\"%s\",\"%s\",\"%s\",%p,%d\n", file, line,
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
    uint16_t chunk_size = *((uint16_t *) pointer - 1);
    return (size_t) chunk_size;
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

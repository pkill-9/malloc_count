/**
 *  Header file to include in a program that makes use of memlog, a
 *  facility for tracking memory allocation in a C program.
 */

#ifndef _MEMLOG_H
#define _MEMLOG_H

// include function definitions.
#include "memlog_functions.h"

// This macro will catch calls to C library malloc and replace them with a
// call to our malloc_log function, which in turn will log the memory 
// allocation, call the real malloc, and return the result. Note that this
// header file must not be included in memlog.c, since we cannot redirect
// the call to the real malloc.
#define malloc(size)    log_malloc (__FILE__, __LINE__, __func__, size)
#define free(pointer)   log_free (__FILE__, __LINE__, __func__, pointer)

#endif // _MEMLOG_H

/** vim: set ft=c ts=4 sw=4 et : */

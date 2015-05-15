/******************************************************************************
 *
 * Header containing prototypes of user-callable functions to retrieve run-time
 * information about malloc()/free() allocation.
 *
 ******************************************************************************
 * Copyright (C) 2013 Timo Bingmann <tb@panthema.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#ifndef _MEMLOG_FUNCTIONS_H
#define _MEMLOG_FUNCTIONS_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" { /* for inclusion from C++ */
#endif

extern void open_memlog (const char *progname);
extern void close_memlog (void);

// these functions handle calls to malloc and free. They should not be
// invoked directly, instead use the macros defined in memlog.h
extern void * malloc_log (const char *file, const char *line, 
  const char *func, size_t bytes);
extern void free_log (const char *file, const char *line, const char *func,
  void *pointer);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MEMLOG_FUNCTIONS_H */

/*****************************************************************************/

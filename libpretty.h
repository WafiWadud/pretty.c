/* SPDX-FileCopyrightText: Artyom Bologov
   SPDX-License-Identifier: BSD-2 Clause */

#ifndef __LIBPRETTY_H__
#define __LIBPRETTY_H__

#include <iso646.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>

/* Function types. */
typedef void (*fn_t) (void);

/* Missing yet useful. */
#define eq ==
/* Fixing inconsistent bit operations. */
#define bitnot ~
#define bitxor ^

/* Lua/Lisp nil. */
#define nil NULL

/* Ternaries. */
#define when
#define unless not
#define then ?
#define otherwise :
#define notherwise : nil
#define only : nil

/* Loops and blocks. Lisp, Lua, BASIC. */
#define until(...) while(not (__VA_ARGS__))
#define repeat do
#define begin {
#define end }

/* For each loop from basically every language. */
#define foreach(type, var, length, ...)                 \
        for (type *init ## __LINE__ = (__VA_ARGS__),    \
                     *var = init ## __LINE__;           \
             var < (init ## __LINE__ + (length));       \
             var++)

#define forrangeby(type, var, init, target, by) \
        for (type var = (init);                 \
             (when ((init) >= (target))         \
              then (var > target)               \
              otherwise (var < target));        \
             (when ((init) >= (target))         \
              then (var = var - (by))           \
              otherwise (var = var + (by))))

/* Ranges from INIT to TARGET. Python. */
#define forrange(var, init, target)                     \
        forrangeby(long long int, var, init, target, 1)

/* Repeat X times. Lisp.
 * Also see repeat keyword for Lua-style loop. */
#define fortimes(var, times)                    \
        forrange(var, 0, times)

/* Tracking and freeing resources. Lisp, Python. */
#define with(close, var, ...)                                   \
        for (void *flag_ ## __LINE__ = (void *) 0,              \
                     *var = (void *) (__VA_ARGS__);             \
             !flag_ ## __LINE__;                                \
             (close)(var), flag_ ## __LINE__ = (void *) 1)

/* Go defer, but rather block scoped and with arbitrary code in it. */
#define defer(...)                                              \
        for (void *flag_ ## __LINE__ = (void *) 0;              \
             !flag_ ## __LINE__;                                \
             flag_ ## __LINE__ = (void *) 1, __VA_ARGS__)

void *_new (size_t size, void *contents)
{
        void *allocated = malloc(size);
        memcpy(allocated, contents, size);
        return allocated;
}

/* Easy resource allocation akin to C++ */
#define new(type, ...) _new(sizeof(type), &((type) {__VA_ARGS__}))

/* Go-style coroutine syntax.*/
thrd_t *go(thrd_start_t fn, void *arg)
{
        thrd_t *thrd = malloc(sizeof(thrd_t));
        thrd_create(thrd, fn, arg);
        return thrd;
}

#endif /* __LIBPRETTY_H__ */

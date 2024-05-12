/*             Author: Benjamin David Lunt
 *                     Forever Young Software
 *                     Copyright (c) 1984-2022
 *  
 *  This code is donated to the Freeware communitee.  You have the
 *   right to use it for learning purposes only.  You may not modify it
 *   for redistribution for any other purpose unless you have written
 *   permission from the author.
 *
 *  You may modify and use it in your own projects as long as they are
 *   for non-profit only and if distributed, have the same requirements.
 *  Any project for profit that uses this code must have written 
 *   permission from the author.
 *
 *  For more information:
 *    http://www.fysnet.net/osdesign_book_series.htm
 *  Contact:
 *    fys [at] fysnet [dot] net
 *
 * Last update:  5 May 2022
 *
 */


#include <libc/malloc.h>
#include <libc/pmm.h>

#define MODNAME "bucket.cpp"

#define MALLOC_FLAGS_VIRTUAL    (1 << 0)   // any memory, physical or linear, non contiguous, any location
#define MALLOC_FLAGS_PHYSICAL   (1 << 1)   // must be physical address and contiguous, inclusive
#define MALLOC_FLAGS_CLEAR      (1 << 2)   // clear the memory on return
#define MALLOC_FLAGS_LOW1MEG    (1 << 3)   // must be before the 1 Meg mark, inclusive
#define MALLOC_FLAGS_LOW16MEG   (1 << 4)   // must be before the 16 Meg mark, inclusive
#define MALLOC_FLAGS_LOW4GIG    (1 << 5)   // must be before the 4 Gig mark, inclusive
#define MALLOC_FLAGS_ALIGNED    (1 << 6)   // must be aligned.  The aligned parameter is now used, else it is ignored.
#define MALLOC_HARDWARE32       (MALLOC_FLAGS_LOW4GIG | MALLOC_FLAGS_PHYSICAL | MALLOC_FLAGS_CLEAR)
#define MALLOC_HARDWARE64       (                       MALLOC_FLAGS_PHYSICAL | MALLOC_FLAGS_CLEAR)

void *mmap(size_t size) {
    return pmm_alloc(size);;
}

void mmap_free(void *ptr, size_t size) {
    pmm_free(ptr, size);
}

void spin_lock(spinlock_t lock) {
}

void spin_unlock(spinlock_t lock) {
}
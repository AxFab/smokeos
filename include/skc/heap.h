/*
 *      This file is part of the SmokeOS project.
 *  Copyright (C) 2015  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#ifndef _SKC_HEAP_H
#define _SKC_HEAP_H 1

#include <skc/stddef.h>
#include <skc/malloc.h>
#include <skc/mcrs.h>
#include <skc/spinlock.h>
#include <skc/llist.h>

#define __HEAP_MMAP 1

#define HEAP_PARANO  (1 << 0)
#define HEAP_CHECK  (1 << 1)
#define HEAP_CORRUPTED  (1 << 2)
#define HEAP_ARENA  (1 << 3)
#define HEAP_MAPPED  (1 << 4)

#define HEAP_HEADER 8
#define HEAP_ALIGN 8
#define HEAP_MAX_CHUNK (64 * _Kib_)
#define HEAP_MIN_CHUNK 16
#define HEAP_ARENA_SIZE (16 * _Mib_)

typedef struct heap_arena heap_arena_t;
typedef struct heap_chunk heap_chunk_t;
typedef struct heap_config heap_config_t;

struct heap_arena 
{
  size_t address_;
  size_t length_;
  size_t used_;
  int flags_;
  spinlock_t lock_;
  heap_chunk_t *free_;  /* Free list */
  llnode_t node_;
};

struct heap_chunk 
{
  unsigned int size_;
  unsigned int prsz_:31;
  unsigned int isfree_:1;
  union {
    char data_[8];
    struct {
      heap_chunk_t *prev_;
      heap_chunk_t *next_;
    }f_;
  }g_;
};


void arena_init(heap_arena_t* arena, size_t address, size_t length);
void* malloc_r(heap_arena_t* arena, size_t len);
void free_r(heap_arena_t* arena, void* ptr);


static inline heap_chunk_t *alloc_chunk(void *ptr)
{
  return pointerof(ptr, heap_chunk_t, g_.data_);
}


#endif  /* _SKC_HEAP_H */

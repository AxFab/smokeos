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
#include <string.h>
#include <errno.h>
#include <skc/heap.h>
#include <skc/mmap.h>
#include <skc/mcrs.h>


static int __empty_arena = 0;
static llhead_t __arenas;
static heap_arena_t __firstArena;

heap_arena_t *new_arena(size_t length) 
{
  ++__empty_arena;
  heap_arena_t *arena = (heap_arena_t*)malloc(sizeof(heap_arena_t));
  void* map = manmap(length, PROT_READ | PROT_WRITE);
  if (map == NULL)
    __FAIL(ENOMEM);
  arena_init(arena, (size_t)map, length);
  ll_append(&__arenas, &arena->node_);
  return arena;
}

void* valloc(size_t len) 
{
  heap_arena_t *arena = (heap_arena_t*)malloc(sizeof(heap_arena_t));
  void* map = manmap(len, PROT_READ | PROT_WRITE);
  arena->address_ = (size_t)map;
  arena->length_ = len;
  arena->flags_ = HEAP_MAPPED;
  /* CREATE ARENA(HEAP_MAPPED) PUSH ON BBTREE */
  return map;
}


void* pvalloc(size_t len)
{
  return valloc(ALIGN_UP(len, PAGE_SIZE));
}


/* Allocate dynamic memory */
void *malloc(size_t size) 
{
  void * ptr = NULL;
  heap_arena_t* arena = NULL;

  if (size > HEAP_MAX_CHUNK && __HEAP_MMAP)
    return valloc(size);

  ll_foreach(&__arenas, arena, heap_arena_t, node_) {
    if (arena->length_ - arena->used_ < size)
      continue;

    if (arena->used_ == 0)
      --__empty_arena;

    ptr = malloc_r(arena, size);
    if (ptr != NULL)
      break;
  }

  if (ptr == NULL) {
    arena = new_arena(HEAP_ARENA_SIZE);
    ptr = malloc_r(arena, size);
  }

  if (__empty_arena == 0) {
    new_arena(HEAP_ARENA_SIZE);
    __empty_arena++;
  }

  return ptr;
}

/* Allocate and clear dynamic memory */
void *calloc(size_t nmemb, size_t size) 
{
  void *ptr;
  size *= nmemb;
  if (size > HEAP_MAX_CHUNK && __HEAP_MMAP)
    return valloc(size);

  ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}


/* Re-allocate dynamic memory */
void *realloc(void *ptr, size_t size)
{
  size_t lg = 0; /* Get chunk size */ 
  void *buf;
  if (lg > size)
    return ptr;
  /* TODO try to grab next item! */
  buf = malloc(size);
  memcpy(buf, ptr, MIN(lg, size));
  free(ptr);
  return buf; 
}


/* Free dynamic memory */
void free(void *ptr)
{
  heap_arena_t* arena = NULL; /* bbtree GET */
  
  if (!(arena->flags_ & HEAP_ARENA) && __HEAP_MMAP) {
    if ((size_t)ptr == arena->address_)
      munmap((void*)arena->address_, arena->length_);
    else
      __FAIL(-1);
    /* Remove from bbtree and free */
  } else if ((size_t)ptr >= arena->address_ && (size_t)ptr < arena->address_ + arena->length_)
    free_r(arena, ptr);
  else 
    __FAIL(-1);
}


void __malloc_init(void* base, size_t len)
{
  __empty_arena = 0;
  memset(&__arenas, 0, sizeof(__arenas));
  memset(&__firstArena, 0, sizeof(__arenas));

  arena_init(&__firstArena, (size_t)base, len);
  ll_append(&__arenas, &__firstArena.node_);
  __empty_arena = 1;
}


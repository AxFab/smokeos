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
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <skc/heap.h>
#include <skc/mcrs.h>


#define arena_prev_chunk(c)  ((heap_chunk_t *)(((size_t)(c))-(c)->prsz_))
#define arena_next_chunk(c)  ((heap_chunk_t *)(((size_t)(c))+(c)->size_))

static void arena_freelist_rm(heap_arena_t* arena, heap_chunk_t *chunk)
{
  assert(spin_is_locked(&arena->lock_));
  chunk->isfree_ = 0;
  arena->used_ += chunk->size_;
  if (chunk->g_.f_.next_ != NULL)
    chunk->g_.f_.next_->g_.f_.prev_ = chunk->g_.f_.prev_;

  if (chunk->g_.f_.prev_ != NULL)
    chunk->g_.f_.prev_->g_.f_.next_ = chunk->g_.f_.next_;
  else {
    /* TODO multi free list */
    arena->free_ = chunk->g_.f_.next_;
  }
  
  chunk->g_.f_.prev_ = (heap_chunk_t *)POISON_PTR;
  chunk->g_.f_.next_ = (heap_chunk_t *)POISON_PTR;
}

static void arena_freelist_add(heap_arena_t* arena, heap_chunk_t *chunk)
{
  /* TODO multi free list */
  heap_chunk_t **list = &arena->free_; 
  heap_chunk_t *cur = arena->free_;
  assert(spin_is_locked(&arena->lock_));
  chunk->isfree_ = 1;
  arena->used_ -= chunk->size_;
  if (cur == NULL) { /* Only free chunk */
    *list = chunk;
    chunk->g_.f_.prev_ = NULL;
    chunk->g_.f_.next_ = NULL;

  } else if (cur->size_ >= chunk->size_) { /* Smallest chunk */
    *list = chunk;
    chunk->g_.f_.prev_ = NULL;
    chunk->g_.f_.next_ = cur;
    cur->g_.f_.prev_ = chunk;
  } else {

    while (cur->g_.f_.next_ && cur->g_.f_.next_->size_ >= chunk->size_)
      cur = cur->g_.f_.next_;

    if (cur->g_.f_.next_) 
      cur->g_.f_.next_->g_.f_.prev_ = chunk;
    chunk->g_.f_.prev_ = cur;
    chunk->g_.f_.next_ = cur->g_.f_.next_;
    cur->g_.f_.next_ = chunk;
  }
}

static heap_chunk_t *arena_split_chunk(heap_arena_t* arena, heap_chunk_t *chunk, size_t len)
{
  heap_chunk_t * split; 
  heap_chunk_t * next = arena_next_chunk(chunk);
  size_t sum = chunk->size_;

  assert (sum >= len + HEAP_MIN_CHUNK);
  chunk->size_ = len;
  split = arena_next_chunk(chunk);
  split->size_ = sum - len;
  split->prsz_ = len;

  if ((size_t)next < arena->address_ + arena->length_)
    next->prsz_ = split->size_;
  return split;
}

static heap_chunk_t *arena_collapse(heap_arena_t* arena, heap_chunk_t *c1, heap_chunk_t *c2)
{
  heap_chunk_t *next;
  c1->size_ += c2->size_;
  next = arena_next_chunk(c1);
  if ((size_t)next < arena->address_ + arena->length_)
    next->prsz_ = c1->size_;
  return c1;
}

static int arena_check(heap_arena_t* arena)
{
  assert(spin_is_locked(&arena->lock_));
  return 0;
}

void arena_init(heap_arena_t* arena, size_t address, size_t length)
{
  heap_chunk_t *first = (heap_chunk_t *)address;
  memset(arena, 0, sizeof(heap_arena_t));
  arena->address_ = address;
  arena->length_ = length;
  arena->flags_ = HEAP_ARENA;
  first->size_ = length;
  first->prsz_ = 0;
  first->g_.f_.prev_ = NULL;
  first->g_.f_.next_ = NULL;
  spin_lock(&arena->lock_);
  arena_freelist_add(arena, first);
  spin_unlock(&arena->lock_);
  arena->used_ = 0;
}

void* malloc_r(heap_arena_t* arena, size_t len)
{
  size_t ck_size = 0;
  heap_chunk_t *ck_prev = NULL;
  heap_chunk_t *cur;
  heap_chunk_t *split;

  len = ALIGN_UP(MAX(len + HEAP_HEADER, HEAP_MIN_CHUNK), HEAP_ALIGN);
  if (len > HEAP_MAX_CHUNK)
    return NULL;

  spin_lock(&arena->lock_);
  if (arena->flags_ & HEAP_PARANO && arena_check(arena)) {
    spin_unlock(&arena->lock_);
    return NULL;
  }

  /* Browse the free chunk list */
  /* TODO multi free list */
  for (cur = arena->free_; cur != NULL; cur = cur->g_.f_.next_) {

    /* If we ask for heap corruption checks */
    if (arena->flags_ & HEAP_CHECK) {
      if (cur->g_.f_.prev_ != ck_prev || cur->size_ < ck_size) {
        arena->flags_ |= HEAP_CORRUPTED;
        spin_unlock(&arena->lock_);
        return NULL;
      }

      ck_size = cur->size_;
      ck_prev = cur;
    }

    /* Loop until the chunk is too small. */
    if (cur->size_ < len) 
      continue;

    arena_freelist_rm(arena, cur);
    if (cur->size_ >= len + HEAP_MIN_CHUNK) {
      split = arena_split_chunk(arena, cur, len);
      arena_freelist_add(arena, split);
    }

    if (arena->flags_ & HEAP_PARANO && arena_check(arena)) {
      spin_unlock(&arena->lock_);
      return NULL;
    }

    spin_unlock(&arena->lock_);
    return cur->g_.data_;
  }

  spin_unlock(&arena->lock_);
  errno = ENOMEM;
  return NULL;
}

void free_r(heap_arena_t* arena, void* ptr)
{
  heap_chunk_t *chunk = alloc_chunk(ptr);
  heap_chunk_t *prev = NULL;
  heap_chunk_t *next = NULL;

  assert((size_t)chunk >= arena->address_);
  assert((size_t)chunk < arena->address_ + arena->length_);
  spin_lock(&arena->lock_);
  if (arena->flags_ & HEAP_PARANO && arena_check(arena)) {
    spin_unlock(&arena->lock_);
    return;
  }

  prev = arena_prev_chunk(chunk);
  next = arena_next_chunk(chunk);

  /* If we ask for heap corruption checks */
  if (arena->flags_ & HEAP_CHECK) {
    if ((prev != chunk && prev->size_ != chunk->prsz_) || 
        (next != chunk && next->prsz_ != chunk->size_)) {
      arena->flags_ |= HEAP_CORRUPTED;
      spin_unlock(&arena->lock_);
      return;
    }
  }

  if ((size_t)next < arena->address_ + arena->length_ && next->isfree_) {
    arena_freelist_rm(arena, next);
    arena_collapse(arena, chunk, next);
  }

  if (prev != chunk && prev->isfree_) {
    arena_freelist_rm(arena, prev);
    arena_collapse(arena, prev, chunk);
    chunk = prev;
  }

  arena_freelist_add(arena, chunk);
  if (arena->flags_ & HEAP_PARANO)
    arena_check(arena);

  spin_unlock(&arena->lock_);
}


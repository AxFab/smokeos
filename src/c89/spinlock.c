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
 *
 *      Implementation of atomic locks.
 */
#include <assert.h>
#include <stddef.h>
#include <skc/spinlock.h>
#include <skc/cpu.h>

static int __lock_counter = 0;
#define THREAD_ID  0

/** Acquires the given lock */
void spin_lock_(spinlock_t* ref, int irq, const char *at)
{
  assert((atomic_read(&ref->key_) & (~1)) == 0);
  // assert(ref->thread_ != THREAD_ID);
  for(;;) {
    while (atomic_read(&ref->key_) != 0) {
      __cpu_pause;
    }

    if (spin_trylock_(ref, irq, at)) {
      return;
    }
  }
}

/** Try to acquired a spin-lock. */
int spin_trylock_(spinlock_t* ref, int irq, const char *at)
{
  assert((atomic_read(&ref->key_) & (~1)) == 0);
  // assert(ref->thread_ != THREAD_ID);
  if (irq) {
    __disable_interupt;
  }

  if (atomic_xchg(&ref->key_, 1) == 0) {
    ++__lock_counter;
    ref->thread_ = THREAD_ID;
    ref->where_ = at;
    return 1;
  }

  if (irq && __lock_counter == 0) {
    __disable_interupt;
  }

  return 0;
}

/** Release given lock. */
void spin_unlock_(spinlock_t* ref, int irq)
{
  assert((atomic_read(&ref->key_) & (~1)) == 0);
  assert(ref->thread_ == THREAD_ID);
  assert(__lock_counter > 0);

  atomic_set(&ref->key_, 0);
  ref->thread_ = -1;
  --__lock_counter;
  if (irq && __lock_counter == 0) {
    __enable_interupt;
  }
}

/** Return 1 if the given lock is currently acquired. */
int spin_is_locked(spinlock_t* ref) 
{
  return atomic_read(&ref->key_) > 0 && __lock_counter > 0;
}


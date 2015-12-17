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
#ifndef _SKC_SPINLOCK_H
#define _SKC_SPINLOCK_H 1

#include <atomic.h>
#include <skc/mcrs.h>

typedef struct spinlock spinlock_t;

/** Common structure that hold information about a spinlock. */
struct spinlock {
  atomic_t key_;
  long thread_;
  const char* where_;
};

#define SPINLOCK_INITIALIZATION { 0, 0, NULL }

#define spin_lock(l) spin_lock_(l,1,__AT__)
#define spin_lock_irq(l) spin_lock_(l,1,__AT__)
#define spin_lock_irqsave(l) spin_lock_(l,1,__AT__)

#define spin_unlock(l) spin_unlock_(l,1)
#define spin_unlock_irq(l) spin_unlock_(l,1)
#define spin_unlock_irqrestore(l) spin_unlock_(l,1)

#define spin_trylock(l) spin_trylock_(l,1,__AT__)

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/** Acquires the given lock */
void spin_lock_(spinlock_t* ref, int irq, const char *at);
/** Try to acquired a spin-lock. */
int spin_trylock_(spinlock_t* ref, int irq, const char *at);
/** Release given lock. */
void spin_unlock_(spinlock_t* ref, int irq);
/** Return true if the given lock is currently acquired. */
int spin_is_locked(spinlock_t* ref);

#endif  /* _SKC_SPINLOCK_H */

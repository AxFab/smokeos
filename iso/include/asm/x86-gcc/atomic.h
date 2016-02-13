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
 *      Implementation of atomic operations.
 */
#ifndef _ASM_ATOMIC_H
#define _ASM_ATOMIC_H 1

typedef struct atomic {
  volatile long v_;
} atomic_t;


/** Increment the referenced counter by one */
static inline void atomic_inc(atomic_t* ref)
{
  //__asm("lock incl %0" : "="(ref->v_));
  ++ref->v_;
}


/** Decrement the referenced counter by one */
static inline void atomic_dec(atomic_t* ref)
{
  --ref->v_;
  // __asm("lock decl %0" : "="(ref->v_));
}


/** Set the referenced counter to the given value */
static inline void atomic_set(atomic_t* ref, long value)
{
  ref->v_ = value;
}


/** Get the referenced counter to the given value */
static inline long atomic_read(atomic_t* ref)
{
  return ref->v_;
}


/** Add the value to the referenced counter and return the resultat */
static inline long atomic_add(atomic_t *ref, long value)
{
  register long temp = value;
  __asm("lock xaddl %%eax, %2;"
        : "=a" (temp) 
        : "a" (temp), "m" (ref->v_) 
        : "memory");
  return temp + value;
}


/** Sub the value to the referenced counter and return the resultat */
static inline long atomic_sub(atomic_t *ref, long value)
{
  return atomic_add(ref, -value);
}


/** Exchange the value and the reference counter and return the resultat */
static inline long atomic_xchg(atomic_t* ref, long value)
{
  register long temp = value;
  __asm("lock xchg %1,%0" 
        : "=m" (ref->v_), "=r" (temp) 
        : "1" (value));
  return temp;
}


#endif  /* _ASM_ATOMIC_H */

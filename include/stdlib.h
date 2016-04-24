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
#ifndef _STDLIB_H
#define _STDLIB_H 1


/* MANUAL ALLOCATION */
#include <skc/malloc.h>


/* PROCESS */
 #define EXIT_FAILURE (-1)
 #define EXIT_SUCCESS (0)
/* Cause abnormal process termination */
void abort(void);
/* Cause normal process termination */
void exit(int status);
/* Get an environment variable */
char *getenv(const char *name);
/* Execute a shell command */
int system(const char *command);
/* Register a function to be called at normal process termination. */
int atexit(void (*function)(void));


/* ARITHMETIC */
/* Returned by `div'.  */
typedef struct { int quot, rem; } div_t;
/* Compute the absolute value of an integer */ 
int abs(int j); 
/* Compute quotient and remainder of an integer division */
div_t div(int numerator, int denominator);

/* Returned by `ldiv'.  */
typedef struct { long int quot, rem; } ldiv_t;
/* Compute the absolute value of an integer */
long int labs(long int j);
/* Compute quotient and remainder of an integer division */
ldiv_t ldiv(long numerator, long denominator);
#ifdef __USE_C99
/* Returned by `ldiv'.  */
typedef struct { long long int quot, rem; } lldiv_t;
/* Compute the absolute value of an integer */
long long int llabs(long long int j);
/* Compute quotient and remainder of an integer division */
lldiv_t lldiv(long long numerator, long long denominator);
#endif


/* NUMBER */
/* Convert ASCII string to floating-point number */
double strtod(const char *nptr, char **endptr);
/* Convert ASCII string to long integer */
long int strtol(const char *nptr, char **endptr, int base);
/* Convert ASCII string to unsigned long integer */
unsigned long int strtoul(const char *nptr, char **endptr, int base);
/* Convert a string to a double */
double atof(const char *nptr);
/* Convert a string to an integer */
int atoi(const char *nptr);
/* Convert a string to an integer */
long atol(const char *nptr);
#ifdef __USE_C99
/* Convert a string to an integer */
long long atoll(const char *nptr);
/* Convert a string to an integer */
long long atoq(const char *nptr);
#endif


/* RANDOM */
#define RAND_MAX 0x7FFF
/* Sets the seed for a new sequence of pseudo-random integers. */
void srand(unsigned int seed);
/* Pseudo-random number generator */
int rand_r(unsigned int *seedp);
int rand(void);


/* ARRAY */
/* Sort an array */
void qsort_r(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg);
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
/* Binary search of a sorted array */
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));


/* MULTI-BYTES CHARACTER */
/* Determine number of bytes in next multibyte character */
int mblen(const char *s, size_t n); 
/* Convert a multibyte string to a wide-character string */
size_t mbstowcs(wchar_t *dest, const char *src, size_t n);
/* Convert a multibyte sequence to a wide character */
int mbtowc(wchar_t *pwc, const char *s, size_t n);
/* Convert a wide-character string to a multibyte string */
size_t wcstombs(char *dest, const wchar_t *src, size_t n);
/* Convert a wide character to a multibyte sequence */
int wctomb(char *s, wchar_t wc);



#endif  /* _STDLIB_H */

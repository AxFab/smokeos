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

/* Searches the first len bytes of array str for character c. */
unsigned char *mbmemchr(const unsigned char *str, int c, size_t len)
{
}

/* Compares two blocks of signed chars. */
int mbmemcmp(const unsigned char *s1, const unsigned char *s2, size_t len)
{
}

/* Copies a block of len bytes from src to dest. */
unsigned char *mbmemcpy(unsigned char *dest, const unsigned char *src, size_t len)
{
}

/* Copies a block of len bytes from src to dest, with possibility of overlaping of source and destination block. */
unsigned char *mbmemmove(unsigned char *dest, const unsigned char *src, size_t len)
{
}

/* Sets num bytes of buffer to byte c. */
unsigned char *mbmemset(unsigned char *buffer, int c, size_t num)
{
}




/* Appends src to dest. */
unsigned char *mbscat(unsigned char *dest, const unsigned char *src)
{
}

/* Finds c in str. */
unsigned char *mbschr(const unsigned char *str, int c)
{
}

/* Compares one string to another. */
int mbscmp(const unsigned char *s1, const unsigned char *s2)
{
}

/* Copies string src to dest. */
unsigned char *mbscpy(unsigned char *dest, const unsigned char *src)
{
}

/* Scans a string. */
size_t mbscspn(const unsigned char *s1, const unsigned char *s2)
{
}

/* Performs case-insensitive string comparison. */
int mbsicmp(const unsigned char *s1, const unsigned char *s1)
{
}

/* Calculates length of a string. */
size_t mbslen(const unsigned char *str)
{
}

/* Appends at most maxlen characters of src to dest. */
unsigned char *mbsncat(unsigned char *dest, const unsigned char *src, size_t maxlen)
{
}

/* Compares at most maxlen characters of one string to another. */
int mbsncmp(const unsigned char *s1, const unsigned char *s2, size_t maxlen)
{
}

/* Copies at most maxlen characters of src to dest. */
unsigned char *mbsncpy(unsigned char *dest, const unsigned char *src, size_t maxlen)
{
}

/* Scans one string for the first occurrence of any character that's in a second string. */
unsigned char *mbspbrk(const unsigned char *s1, const unsigned char *s2)
{
}

/* Finds the last occurrence of c in str. */
unsigned char *mbsrchr(const unsigned char *str, int c)
{
}

/* Scans a string for a segment that is a subset of a set of characters. */
size_t mbsspn(const unsigned char *s1, const unsigned char *s2)
{
}

/* Finds the first occurrence of a substring in another string. */
unsigned char *mbsstr(const unsigned char *str, const unsigned char *substr)
{
}

/* Scans s1 for the first token not contained in s2. */
unsigned char *mbstok(unsigned char *s1, const unsigned char *s2)
{
}

/* duplicate a string  */
unsigned char *mbsdup(const unsigned char *str)
{
}

/* duplicate a string at most maxlen characters */
unsigned char *mbsndup(const unsigned char *str, size_t maxlen)
{
}

/* Convert a string to lowercase. */
unsigned char *mbslwr(unsigned char *str)
{
}

/* Convert a string to uppercase. */
unsigned char *mbsupr(unsigned char *string)
{
}

/* Compare characters of two strings without regard to case. */
int mbsnicmp(const unsigned char *s1, const unsigned char *s2, size_t maxlen)
{
}

/* Reverse characters of a string. */
unsigned char *mbsrev(unsigned char *string)
{
}

/* Set characters of a string to a character. */
unsigned char *mbsset(unsigned char *str, int c)
{
}

/* Initialize characters of a string to a given format. */
unsigned char *mbsnset(unsigned char *str, int c, size_t maxlen)
{
}




/* Compare strings using locale-specific information. */
int mbscoll(const unsigned char *s1, const unsigned char *s2)
{
}

/* Compare strings using locale-specific information. */
int mbsicoll(const unsigned char *s1, const unsigned char *s2)
{
}

/* Compare strings using locale-specific information. */
int mbsncoll(const unsigned char *s1, const unsigned char *s2, size_t maxlen)
{
}

/* Compare strings using locale-specific information. */
int mbsnicoll(const unsigned char *s1, const unsigned char *s2, size_t maxlen)
{
}

/* String transformation */ 
size_t mbsxfrm(char *dest, const char *src, size_t n)
{
}



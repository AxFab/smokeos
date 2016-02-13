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
wchar_t *wmemchr(const wchar_t *str, int c, size_t len)
{
}

/* Compares two blocks of signed chars. */
int wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t len)
{
}

/* Copies a block of len bytes from src to dest. */
wchar_t *wmemcpy(wchar_t *dest, const wchar_t *src, size_t len)
{
}

/* Copies a block of len bytes from src to dest, with possibility of overlaping of source and destination block. */
wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t len)
{
}

/* Sets num bytes of buffer to byte c. */
wchar_t *wmemset(wchar_t *buffer, int c, size_t num)
{
}




/* Appends src to dest. */
wchar_t *wcscat(wchar_t *dest, const wchar_t *src)
{
}

/* Finds c in str. */
wchar_t *wcschr(const wchar_t *str, int c)
{
}

/* Compares one string to another. */
int wcscmp(const wchar_t *s1, const wchar_t *s2)
{
}

/* Copies string src to dest. */
wchar_t *wcscpy(wchar_t *dest, const wchar_t *src)
{
}

/* Scans a string. */
size_t wcscspn(const wchar_t *s1, const wchar_t *s2)
{
}

/* Performs case-insensitive string comparison. */
int wcsicmp(const wchar_t *s1, const wchar_t *s1)
{
}

/* Calculates length of a string. */
size_t wcslen(const wchar_t *str)
{
}

/* Appends at most maxlen characters of src to dest. */
wchar_t *wcsncat(wchar_t *dest, const wchar_t *src, size_t maxlen)
{
}

/* Compares at most maxlen characters of one string to another. */
int wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t maxlen)
{
}

/* Copies at most maxlen characters of src to dest. */
wchar_t *wcsncpy(wchar_t *dest, const wchar_t *src, size_t maxlen)
{
}

/* Scans one string for the first occurrence of any character that's in a second string. */
wchar_t *wcspbrk(const wchar_t *s1, const wchar_t *s2)
{
}

/* Finds the last occurrence of c in str. */
wchar_t *wcsrchr(const wchar_t *str, int c)
{
}

/* Scans a string for a segment that is a subset of a set of characters. */
size_t wcsspn(const wchar_t *s1, const wchar_t *s2)
{
}

/* Finds the first occurrence of a substring in another string. */
wchar_t *wcsstr(const wchar_t *str, const wchar_t *substr)
{
}

/* Scans s1 for the first token not contained in s2. */
wchar_t *wcstok(wchar_t *s1, const wchar_t *s2)
{
}

/* duplicate a string  */
wchar_t *wcsdup(const wchar_t *str)
{
}

/* duplicate a string at most maxlen characters */
wchar_t *wcsndup(const wchar_t *str, size_t maxlen)
{
}

/* Convert a string to lowercase. */
wchar_t *wcslwr(wchar_t *str)
{
}

/* Convert a string to uppercase. */
wchar_t *wcsupr(wchar_t *string)
{
}

/* Compare characters of two strings without regard to case. */
int wcsnicmp(const wchar_t *s1, const wchar_t *s2, size_t maxlen)
{
}

/* Reverse characters of a string. */
wchar_t *wcsrev(wchar_t *string)
{
}

/* Set characters of a string to a character. */
wchar_t *wcsset(wchar_t *str, int c)
{
}

/* Initialize characters of a string to a given format. */
wchar_t *wcsnset(wchar_t *str, int c, size_t maxlen)
{
}




/* Compare strings using locale-specific information. */
int wcscoll(const wchar_t *s1, const wchar_t *s2)
{
}

/* Compare strings using locale-specific information. */
int wcsicoll(const wchar_t *s1, const wchar_t *s2)
{
}

/* Compare strings using locale-specific information. */
int wcsncoll(const wchar_t *s1, const wchar_t *s2, size_t maxlen)
{
}

/* Compare strings using locale-specific information. */
int wcsnicoll(const wchar_t *s1, const wchar_t *s2, size_t maxlen)
{
}

/* String transformation */ 
size_t wcsxfrm(char *dest, const char *src, size_t n)
{
}



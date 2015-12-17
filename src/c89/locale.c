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
#include <locale.h>
#include <string.h>

#define _C(n)  ((char)n)

#define CHAR_MAX 127
#define ENCODING_LEN 7
static char __ctype_charset[ENCODING_LEN + 1] = "ASCII";
/* static char __ctype_charset[ENCODING_LEN + 1] = "UTF-8"; */

static struct lconv __lconv = 
{
  ".", "", "", "", "", "", "", "", "", "",
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  CHAR_MAX, CHAR_MAX, CHAR_MAX, CHAR_MAX,
  CHAR_MAX, CHAR_MAX
};

/* Get numeric formatting information */
struct lconv *localeconv(void)
{
  return &__lconv;
}

/* Set the current locale */
char *setlocale(int category, const char *locale)
{
#ifndef __USE_MBC
  if (locale && strcmp(locale, "POSIX") && 
      strcmp(locale, "C") && strcmp(locale, ""))
    return NULL;
  return "C";
#else
  /* ... */
#endif
}


char *__locale_charset(void)
{
  /* return __get_current_ctype_locale ()->codeset; */
  return __ctype_charset;
}

typedef struct mbstate {
  int __count;
} mbstate_t;


int ascii_mbtowc(const char *buf, size_t len, mbstate_t *state)
{
  return (buf[0] < 0) ? -1 : buf[0];
}

int utf8_mbtowc(const char *buf, size_t len, mbstate_t *state)
{
  int val;
  if (buf[0] > 0) {
    val = buf[0];

  } else if (buf[0] > _C(0xc0)) {
    val = -1;

  } else if (buf[0] > _C(0xe0) && len >= 2 && buf[1] < 0) {
    val = (buf[0] & 0x1F) | (buf[1] & 0x3F);
    state->__count = 2;

  } else if (buf[0] > _C(0xf0) && len >= 3 && buf[1] < 0 && buf[2] < 0) {
    val = (buf[0] & 0x0F) | (buf[1] & 0x3F) | (buf[2] & 0x3F);
    state->__count = 3;

  } else if (len >= 4 && buf[1] < 0 && buf[2] < 0 && buf[3] < 0) {
    val = (buf[0] & 0x07) | (buf[1] & 0x3F) | (buf[2] & 0x3F) | (buf[3] & 0x3F);
    state->__count = 4;

  } else {
    val = -1;
  }

  return val;
}

int __mbtowc(wchar_t *ref, const char *buf, size_t len, const char *charset, mbstate_t *state)
{
  int val = -1; 
  state->__count = 1;
  if (strcmp(charset, "ASCII") == 0)
    val = ascii_mbtowc(buf, len, state);
  else if (strcmp(charset, "UTF-8") == 0)
    val = ascii_mbtowc(buf, len, state);

  if (val > 0 && ref)
    *ref = val;

  return val;
}


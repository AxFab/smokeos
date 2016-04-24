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
#include <time.h>
#include <assert.h>
#include <errno.h>

int snprintf(char *, int, const char *, ...);

#ifdef __USE_C99
#  define __long long long
#  define _LG(i) i ## LL
#define _LG_MAX (2147483647LL * 31622400LL)
#else
#  define  __long long
#  define _LG(i) i ## L
#define _LG_MAX 2147483647
#endif

#define _LG_MIN (-_LG_MAX - 1)


/* 2000-03-01 (mod 400 year, immediately after feb29 */
#define LEAPOCH (_LG(946684800) + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)


#undef INT_MAX
#define INT_MAX ((int)2147483647)

#undef INT_MIN
#define INT_MIN ((int)-INT_MAX - 1)


/* move epoch from 01.01.1970 to 01.03.2000 - this is the first day of new
 * 400-year long cycle, right after additional day of leap year. This adjustment
 * is required only for date calculation, so instead of modifying time_t value
 * (which would require 64-bit operations to work correctly) it's enough to
 * adjust the calculated number of days since epoch. */
#define EPOCH_ADJUSTMENT_DAYS 11017
/* year to which the adjustment was made */
#define ADJUSTED_EPOCH_YEAR 2000
/* 1st March of 2000 is Wednesday */
#define ADJUSTED_EPOCH_WDAY 3
/* there are 97 leap years in 400-year periods. ((400 - 97) * 365 + 97 * 366) */
#define DAYS_PER_400_YEARS  146097L
/* there are 24 leap years in 100-year periods. ((100 - 24) * 365 + 24 * 366) */
#define DAYS_PER_100_YEARS  36524L
/* there is one leap year every 4 years */
#define DAYS_PER_4_YEARS  (3 * 365 + 366)
/* number of days in a non-leap year */
#define DAYS_PER_YEAR   365
/* number of days in January */
#define DAYS_IN_JANUARY   31
/* number of days in non-leap February */
#define DAYS_IN_FEBRUARY  28

#define YEAR_BASE 1900
#define DAYSPERWEEK 7
#define MONSPERYEAR 12
#define SECSPERMIN 60
#define SECSPERHOUR 3600
#define SECSPERHOURS 3600
#define SECSPERDAY (SECSPERHOURS*24)

static const char *const weekDayStrings[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};


static const char *const shWeekDayStrings[] = {
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};


static const char *const shMonthStrings[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const int __month_lengths[2][MONSPERYEAR] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static __long __yeartosecs(int year, int *pLeap)
{
  int cycles, centuries, leaps, rem, isLeap;
  if (year - _LG(2) <= 136) {
    int y = year;
    int leaps = (y - 68) >> 2;

    if (!((y - 68) & 3)) {
      leaps--;
      isLeap = 1;
    } else {
      isLeap = 0;
    }

    return 31536000 * (y - 70) + 86400 * leaps;
  }

  cycles = (year - 100) / 400;

  rem = (year - 100) % 400;

  if (rem < 0) {
    cycles--;
    rem += 400;
  }

  if (!rem) {
    isLeap = 1;
    centuries = 0;
    leaps = 0;
  } else {
    if (rem >= 200) {
      if (rem >= 300) centuries = 3, rem -= 300;
      else centuries = 2, rem -= 200;
    } else {
      if (rem >= 100) centuries = 1, rem -= 100;
      else centuries = 0;
    }

    if (!rem) {
      isLeap = 0;
      leaps = 0;
    } else {
      leaps = rem / 4U;
      rem %= 4U;
      isLeap = !rem;
    }
  }

  leaps += 97 * cycles + 24 * centuries - isLeap;
  if (pLeap)
    *pLeap = isLeap;
  return (year - 100) * _LG(31536000) + leaps * _LG(86400) + 946684800 + 86400;
}


static int __monthtosecs(int month, int is_leap)
{
  static const int secs_through_month[] = {
    0, 31 * 86400, 59 * 86400, 90 * 86400,
    120 * 86400, 151 * 86400, 181 * 86400, 212 * 86400,
    243 * 86400, 273 * 86400, 304 * 86400, 334 * 86400
  };
  int t = secs_through_month[month];

  if (is_leap && month >= 2) t += 86400;

  return t;
}


static __long __tmtosecs(const struct tm *tm)
{
  __long t;
  int is_leap;
  int year = tm->tm_year;
  int month = tm->tm_mon;

  if (month >= 12 || month < 0) {
    int adj = month / 12;
    month %= 12;

    if (month < 0) {
      adj--;
      month += 12;
    }

    year += adj;
  }

  t = __yeartosecs(year, &is_leap);
  t += __monthtosecs(month, is_leap);
  t += _LG(86400) * (tm->tm_mday - 1);
  t += _LG(3600) * tm->tm_hour;
  t += _LG(60) * tm->tm_min;
  t += tm->tm_sec;
  return t;
}

static int __secstotm(__long t, struct tm *tm)
{
  __long days, secs;
  int remdays, remsecs, remyears;
  int qc_cycles, c_cycles, q_cycles;
  int years, months;
  int wday, yday, leap;
  static const char days_in_month[] = {31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29};

  /* Reject time_t values whose year would overflow int */
  if (t < _LG_MIN || t > _LG_MAX)
    return -1;

  secs = t - LEAPOCH;
  days = secs / 86400;
  remsecs = secs % 86400;

  if (remsecs < 0) {
    remsecs += 86400;
    days--;
  }

  wday = (3 + days) % 7;

  if (wday < 0) wday += 7;

  qc_cycles = days / DAYS_PER_400Y;
  remdays = days % DAYS_PER_400Y;

  if (remdays < 0) {
    remdays += DAYS_PER_400Y;
    qc_cycles--;
  }

  c_cycles = remdays / DAYS_PER_100Y;

  if (c_cycles == 4) c_cycles--;

  remdays -= c_cycles * DAYS_PER_100Y;

  q_cycles = remdays / DAYS_PER_4Y;

  if (q_cycles == 25) q_cycles--;

  remdays -= q_cycles * DAYS_PER_4Y;

  remyears = remdays / 365;

  if (remyears == 4) remyears--;

  remdays -= remyears * 365;

  leap = !remyears && (q_cycles || !c_cycles);
  yday = remdays + 31 + 28 + leap;

  if (yday >= 365 + leap) yday -= 365 + leap;

  years = remyears + 4 * q_cycles + 100 * c_cycles + 400 * qc_cycles;

  for (months = 0; days_in_month[months] <= remdays; months++)
    remdays -= days_in_month[months];

  if (years + 100 > INT_MAX || years + 100 < INT_MIN)
    return -1;

  tm->tm_year = years + 100;
  tm->tm_mon = months + 2;

  if (tm->tm_mon >= 12) {
    tm->tm_mon -= 12;
    tm->tm_year++;
  }

  tm->tm_mday = remdays + 1;
  tm->tm_wday = wday;
  tm->tm_yday = yday;

  tm->tm_hour = remsecs / 3600;
  tm->tm_min = remsecs / 60 % 60;
  tm->tm_sec = remsecs % 60;

  return 0;
}

/* -- FIXME use local */
char *asctime_r(const struct tm *date, char *str)
{
  assert(date->tm_wday >= 0 && date->tm_wday < 7);
  assert(date->tm_mon >= 0 && date->tm_mon < 12);
  snprintf(str, 26, "%.3s %.3s %3d %.2d:%.2d:%.2d %d\n",
           shWeekDayStrings[date->tm_wday], shMonthStrings[date->tm_mon],
           date->tm_mday, date->tm_hour,
           date->tm_min, date->tm_sec,
           1900 + date->tm_year);
  return str;
}


time_t timegm(struct tm *tm)
{
  struct tm datetime;
  __long t = __tmtosecs(tm);

  if (__secstotm(t, &datetime) < 0) {
    errno = EOVERFLOW;
    return -1;
  }

  *tm = datetime;
  tm->tm_isdst = 0;
  return t;
}


struct tm *gmtime_r(const time_t * timep, struct tm *res)
{
  long days, rem;
  const time_t lcltime = *timep;
  int year, month, yearday, weekday;
  int years400, years100, years4, remainingyears;
  int yearleap;
  const int *ip;

  days = ((long)lcltime) / SECSPERDAY - EPOCH_ADJUSTMENT_DAYS;
  rem = ((long)lcltime) % SECSPERDAY;
  if (rem < 0) {
    rem += SECSPERDAY;
    --days;
  }

  /* compute hour, min, and sec */
  res->tm_hour = (int) (rem / SECSPERHOUR);
  rem %= SECSPERHOUR;
  res->tm_min = (int) (rem / SECSPERMIN);
  res->tm_sec = (int) (rem % SECSPERMIN);

  /* compute day of week */
  if ((weekday = ((ADJUSTED_EPOCH_WDAY + days) % DAYSPERWEEK)) < 0)
    weekday += DAYSPERWEEK;
  res->tm_wday = weekday;

  /* compute year & day of year */
  years400 = days / DAYS_PER_400_YEARS;
  days -= years400 * DAYS_PER_400_YEARS;
  /* simplify by making the values positive */
  if (days < 0) {
    days += DAYS_PER_400_YEARS;
    --years400;
  }

  years100 = days / DAYS_PER_100_YEARS;
  if (years100 == 4) /* required for proper day of year calculation */
    --years100;
  days -= years100 * DAYS_PER_100_YEARS;
  years4 = days / DAYS_PER_4_YEARS;
  days -= years4 * DAYS_PER_4_YEARS;
  remainingyears = days / DAYS_PER_YEAR;
  if (remainingyears == 4) /* required for proper day of year calculation */
    --remainingyears;
  days -= remainingyears * DAYS_PER_YEAR;

  year = ADJUSTED_EPOCH_YEAR + years400 * 400 + years100 * 100 + years4 * 4 +
      remainingyears;

  /* If remainingyears is zero, it means that the years were completely
   * "consumed" by modulo calculations by 400, 100 and 4, so the year is:
   * 1. a multiple of 4, but not a multiple of 100 or 400 - it's a leap year,
   * 2. a multiple of 4 and 100, but not a multiple of 400 - it's not a leap
   * year,
   * 3. a multiple of 4, 100 and 400 - it's a leap year.
   * If years4 is non-zero, it means that the year is not a multiple of 100 or
   * 400 (case 1), so it's a leap year. If years100 is zero (and years4 is zero
   * - due to short-circuiting), it means that the year is a multiple of 400
   * (case 3), so it's also a leap year. */
  yearleap = remainingyears == 0 && (years4 != 0 || years100 == 0);

  /* adjust back to 1st January */
  yearday = days + DAYS_IN_JANUARY + DAYS_IN_FEBRUARY + yearleap;
  if (yearday >= DAYS_PER_YEAR + yearleap) {
    yearday -= DAYS_PER_YEAR + yearleap;
    ++year;
  }

  res->tm_yday = yearday;
  res->tm_year = year - YEAR_BASE;

  /* Because "days" is the number of days since 1st March, the additional leap
   * day (29th of February) is the last possible day, so it doesn't matter much
   * whether the year is actually leap or not. */
  ip = __month_lengths[1];
  month = 2;
  while (days >= ip[month]) {
    days -= ip[month];
    if (++month >= MONSPERYEAR)
      month = 0;
  }
  res->tm_mon = month;
  res->tm_mday = days + 1;

  res->tm_isdst = 0;

  return res;
}


/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* Transform date and time to ASCII */
char *asctime(const struct tm *tm)
{
  static char buf[30];
  return asctime_r(tm, buf);
}

/* Transform date and time to ASCII */ 
char *ctime(const time_t *timep)
{
  struct tm buf;
  return asctime(gmtime_r(timep, &buf));
}

/* The number of seconds elapsed between time time1 and time time0, 
 * represented as a double. */
double difftime(time_t time1, time_t time0)
{
  return time1 - time0;
}

/* Transform date and time to broken-down time */
struct tm *gmtime(const time_t *timep)
{
  static struct tm buf;
  return gmtime_r(timep, &buf);
}

/* Transform date and time to broken-down time */
struct tm *localtime(const time_t *timep)
{
  time_t local = *timep + 0;
  static struct tm buf;
  return gmtime_r(&local, &buf);
}

/* Transform broken-down time to timestamp */
time_t mktime(struct tm *tm)
{
  return timegm(tm);
}

/* Format date and time */
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);



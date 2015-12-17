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
#include <sys/types.h>
#include <skc/iofile.h>

/* Stream open functions */
FILE *fopen(const char *path, const char *mode);
/* Stream open functions */
FILE *fdopen(int fd, const char *mode);
/* Stream open functions */
FILE *freopen(const char *path, const char *mode, FILE *stream);
/* Stream close functions */
int fclose(FILE *stream);


/* Binary stream input */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream );
/* Binary stream output */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);


/* Seek from beginning of file.  */
#define SEEK_SET  0
/* Seek from current position.  */
#define SEEK_CUR  1
/* Seek from end of file.  */
#define SEEK_END  2

/* Reposition a stream */
int fseek(FILE *stream, long offset, int whence);
/* Reposition a stream */
long ftell(FILE *stream);
/* Reposition a stream */
void rewind(FILE *stream);
/* Reposition a stream */
int fgetpos(FILE *stream, fpos_t *pos);
/* Reposition a stream */
int fsetpos(FILE *stream, fpos_t *pos); 


/* Check and reset stream status */
void clearerr(FILE *stream);
/* Check and reset stream status */
int feof(FILE *stream);
/* Check and reset stream status */
int ferror(FILE *stream);
/* Check and reset stream status */
int fileno(FILE *stream); 


/* Flush a stream */
int fflush(FILE *stream);


/* Fully buffered  */
#define _IOFBF 0
/* Line buffered */
#define _IOLBF 1
/* Unbuffered */
#define _IONBF 2

/* Stream buffering operations */
void setbuf(FILE *stream, char *buf);
/* Stream buffering operations */
int setvbuf(FILE *stream, char *buf, int mode, size_t size);


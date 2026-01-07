#include "fio.h"

#include "syscall.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

FILE _iob[OPEN_MAX] = {
    /* stdin, stdout, stderr: */
    {0, (char*) 0, (char*) 0, _READ, 0},
    {0, (char*) 0, (char*) 0, _WRITE, 1},
    {0, (char*) 0, (char*) 0, _WRITE | _UNBUF, 2}};

int _fillbuf(FILE* fp) {
  size_t bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

  if (fp->base == NULL)
    if ((fp->base = (char*) malloc(bufsize)) == NULL)
      return EOF;
  fp->ptr = fp->base;
  fp->count = read(fp->fd, fp->ptr, bufsize);
  if (--fp->count < 0) {
    if (fp->count == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->count = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}

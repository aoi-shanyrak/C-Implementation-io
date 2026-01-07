#define NULL 0
#define EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20 // max opened files

enum _flags {
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020
};

typedef struct _iobuf {
  int count;  // count last symbols
  char* ptr;  // next pos
  char* base; // place of buf
  int flag;   // mode
  int fd;     // descryptor file
} FILE;

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

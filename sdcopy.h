#ifdef MS_WINDOWS
#define INPUT_FILE_MODE O_RDONLY|O_BINARY
#define OUTPUT_FILE_MODE O_CREAT|O_WRONLY|O_BINARY
#define file_seek _lseeki64
#endif
#ifdef UNIX_32
#define _LARGEFILE64_SOURCE
#define INPUT_FILE_MODE O_RDONLY|O_LARGEFILE
#define OUTPUT_FILE_MODE O_CREAT|O_WRONLY|O_LARGEFILE
#define file_seek lseek64
#endif
#ifdef UNIX_64
#define INPUT_FILE_MODE O_RDONLY
#define OUTPUT_FILE_MODE O_CREAT|O_WRONLY
#define file_seek lseek
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
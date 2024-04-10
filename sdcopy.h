#if defined _MSC_VER && _MSC_VER>=1400
  #pragma warning(disable : 4996)
#endif

#ifndef _WIN32
#define _LARGEFILE64_SOURCE
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _WIN32
#include <io.h>
#define INPUT_FILE_MODE O_RDONLY|O_BINARY
#define OUTPUT_FILE_MODE O_CREAT|O_WRONLY|O_BINARY
#define OUTPUT_FILE_PERMISSIONS S_IREAD|S_IWRITE
#define lseek64 _lseeki64
#else
#include <unistd.h>
#define INPUT_FILE_MODE O_RDONLY|O_LARGEFILE
#define OUTPUT_FILE_MODE O_CREAT|O_WRONLY|O_LARGEFILE
#define OUTPUT_FILE_PERMISSIONS S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif
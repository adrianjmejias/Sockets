#ifndef UTIL
#define UTIL
#include <stdio.h>
//#include <sys/stat.h>
//#define MAXPATH 256 FILENAME_MAX

#define FRAGMENT_SIZE 500

enum bool { false, true;};
#define perror(msg) printf(msg)
#define DieWithError(msg) perror(msg); exit(-1) 

#endif // end #ifndef UTIL

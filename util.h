
#ifndef UTIL
#define UTIL

#define MAXPATH 256
#define FRAGMENT_SIZE 500

enum bool { false, true;}
#define perror(msg) printf(msg)
#define DieWithError(msg) perror(msg); exit(-1) 

#endif // end #ifndef UTIL
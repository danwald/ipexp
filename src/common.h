#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>

#ifndef  DEBUG
     #define   PRINT(arg)
#else
     #define   PRINT(arg)     printf arg
#endif

const int PORT=8080;
const int WS_THREADS=16;
const std::string CMP_HEADER("cmp");
const std::string CMP_PH_VALUE("phash");
const std::string CMP_MD5_VALUE("md5");

typedef enum { ERROR=-1, PRESENT=0, ABSENT=1, ADDED=2} Result;
#endif

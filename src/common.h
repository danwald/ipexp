#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>


const int PORT=8080;
const int WS_THREADS=8;
const std::string CMP_HEADER("CMP");

typedef enum { PRESENT=0, ABSENT=1, ADDED=2 } Result;
#endif

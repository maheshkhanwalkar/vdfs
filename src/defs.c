#include "defs.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    vfprintf(stderr, msg, args);
    exit(1);
}

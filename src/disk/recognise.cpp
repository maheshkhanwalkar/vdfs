#include "recognise.h"
#include "disk/raw/raw_handler.h"

handler* find_handler(FILE* fp)
{
    return new raw_handler(fp);
}

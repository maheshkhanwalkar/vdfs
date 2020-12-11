#include "raw_handler.h"

int raw_handler::read(char* buffer, int amt, int pos)
{
    fseek(this->fp, pos, SEEK_SET);
    return fread(buffer, amt, 1, fp);
}

int raw_handler::write(char* buffer, int amt, int pos)
{
    fseek(this->fp, pos, SEEK_SET);
    return fwrite(buffer, amt, 1, fp);
}

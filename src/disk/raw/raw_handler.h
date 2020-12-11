#pragma once
#include "../handler.h"

class raw_handler: public handler
{
public:
    explicit raw_handler(FILE* fp): handler(fp) {}

    int read(char *buffer, int amt, int pos) override;
    int write(char *buffer, int amt, int pos) override;
};

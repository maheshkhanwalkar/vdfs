#pragma once
#include "disk/handler.h"
#include <unordered_map>

namespace __raw_handler {
    struct part
    {
        uint64_t b_start;
        uint64_t b_end;
    };
};

class raw_handler: public handler
{
public:
    explicit raw_handler(FILE* fp);

    bool is_valid(int part) override;

    int read(int part, char *buffer, uint64_t amt, uint64_t pos) override;
    int write(int part, char *buffer, uint64_t amt, uint64_t pos) override;

    std::unordered_map<int, __raw_handler::part> partitions;
};

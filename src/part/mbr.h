#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "defs.h"

bool is_mbr(FILE* fp, reader read_sector);
part_t* mbr_partitions(FILE* fp, reader read_sector, size_t* count);

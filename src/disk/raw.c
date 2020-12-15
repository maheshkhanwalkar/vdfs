#include "raw.h"
#include "part/mbr.h"
#include "defs.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum part_type {
    MBR
} part_type_t;

static bool read_sector(uint64_t sector, FILE* fp, char* buffer)
{
    fseek(fp, (long)sector * SECTOR_SIZE, SEEK_SET);
    size_t res = fread(buffer, SECTOR_SIZE, 1, fp);

    return res == 1;
}

static part_type_t detect(FILE* fp)
{
    if(is_mbr(fp, read_sector))
        return MBR;

    fclose(fp);
    die("unknown disk format");
}

void mount_raw_disk(const char* disk, const char* mount)
{
    FILE* fp = fopen(disk, "rb");
    part_type_t type = detect(fp);

    part_t* parts = NULL;
    size_t count = 0;

    if(type == MBR) {
        parts = mbr_partitions(fp, read_sector, &count);
    }

    // TODO setup a loop device for each partition
    fclose(fp);
    free(parts);
}

#include "handler.h"
#include "defs.h"
#include "raw.h"

#include <stdio.h>

typedef enum disk_type {
    RAW
} disk_type_t;

static disk_type_t detect(FILE* fp)
{
    UNUSED(fp)
    return RAW;
}

void mount_disk(const char* disk, const char* mount)
{
    FILE* fp = fopen(disk, "rb");

    if(!fp) {
        die("could not open: %s", disk);
    }

    disk_type_t type = detect(fp);
    fclose(fp);

    switch (type) {
        case RAW:
            mount_raw_disk(disk, mount);
            break;
        default:
            die("internal error: unknown disk type");
    }
}

void umount_disk(const char* mount)
{
    // TODO
}

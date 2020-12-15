#include "mbr.h"
#include <stdlib.h>

#define MBR_BOOT_MAGIC 0xAA55
#define MBR_GPT_PART 0xEE
#define MBR_MAX_PARTITIONS 4

/**
 * MBR partition format
 */
typedef struct mbr_part {
    unsigned char status;
    unsigned char chs_first[3];
    unsigned char part_type;
    unsigned char chs_last[3];
    uint32_t lba_first;
    uint32_t num_sectors;
} __attribute__((packed)) mbr_part_t;

/**
 * Modern MBR format
 */
typedef struct mbr {
    unsigned char boot1[218];
    unsigned char time_stamp[6];
    unsigned char boot2[216];
    uint32_t disk_sig;
    uint16_t copy_protect;
    mbr_part_t partitions[4];
    uint16_t boot_sig;
} __attribute__((packed)) mbr_t;


static mbr_t* read_mbr(FILE* fp, reader read_sector, char* buffer)
{
    bool res = read_sector(0, fp, buffer);

    if(!res) {
        fclose(fp);
        die("error. could not read disk image");
    }

    return (mbr_t*)buffer;
}

bool is_mbr(FILE* fp, reader read_sector)
{
    char buffer[SECTOR_SIZE];
    mbr_t* mbr = read_mbr(fp, read_sector, buffer);

    // No boot magic
    if(mbr->boot_sig != MBR_BOOT_MAGIC)
        return false;

    // Protective MBR, so actually GPT partitioned
    if(mbr->partitions[0].part_type == MBR_GPT_PART)
        return false;

    return true;
}

part_t* mbr_partitions(FILE* fp, reader read_sector, size_t* count)
{
    char buffer[SECTOR_SIZE];
    mbr_t* mbr = read_mbr(fp, read_sector, buffer);

    size_t amt = 0;

    for(; amt < MBR_MAX_PARTITIONS; amt++) {
        if(mbr->partitions[amt].num_sectors == 0)
            break;
    }

    part_t* all = calloc(amt, sizeof(*all));

    for(size_t s = 0; s < amt; s++) {
        all[s].start = mbr->partitions[s].lba_first * SECTOR_SIZE;
        all[s].end = all[s].start + mbr->partitions[s].num_sectors * SECTOR_SIZE;
    }

    return all;
}

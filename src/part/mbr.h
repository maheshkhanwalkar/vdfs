#pragma once
#include <cstdint>

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


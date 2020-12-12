#define FUSE_USE_VERSION 40

#include <fuse3/fuse.h>
#include <cstdio>

#include "disk/recognise.h"
#include "ops/fs_ops.h"

struct fuse_operations opt = {
    .getattr = fs_getattr,
    .open = fs_open,
};

/**
 * Disk handler global variable
 */
handler* disk_hd = nullptr;

int main(int argc, const char* argv[])
{
    if(argc < 3) {
        fprintf(stderr, "error. missing mount-point and/or disk image\n");
        return -1;
    }

    if(argc > 3) {
        fprintf(stderr, "error. too many arguments provided. format: vdfs disk.img /where/to/mount\n");
        return -1;
    }

    const char* disk = argv[1];
    FILE* fp = fopen(disk, "a+b");

    if(!fp) {
        fprintf(stderr, "could not mount %s: bad path\n", disk);
        return -1;
    }

    disk_hd = find_handler(fp);

    if(!disk_hd) {
        fprintf(stderr, "could not mount %s: unrecognised format\n", disk);
        fclose(fp);

        return -1;
    }

    char* args[5] = {(char*)argv[0], (char*)argv[2], "-f", "-s", "-d"};
    return (int)fuse_main(5, args, &opt, nullptr);
}

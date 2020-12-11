#define FUSE_USE_VERSION 40

#include <fuse3/fuse.h>
#include <cstdio>

#include "disk/recognise.h"

// TODO
struct fuse_operations opt = {

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

    char* args[2] = {(char*)argv[0], (char*)argv[2]};
    return (int)fuse_main(2, args, &opt, nullptr);
}

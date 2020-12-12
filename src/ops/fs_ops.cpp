#include "fs_ops.h"
#include "disk/handler.h"

#define FUSE_USE_VERSION 30
#include <fuse3/fuse.h>
#include <cstdio>
#include <unistd.h>

#include <string>

extern handler* disk_hd;

int fs_open(const char* file, struct fuse_file_info* fi)
{
    printf("file opened: %s\n", file);
    return 0;
}

int fs_getattr(const char* file, struct stat* st, struct fuse_file_info* fi)
{
    std::string f_str(file);

    // TODO: handle stat() on the partition files...
    if(f_str == "/") {
        st->st_uid = getuid();
        st->st_gid = getgid();

        st->st_mode = __S_IFDIR;
        st->st_nlink = 0;

        return 0;
    } else {
        return -ENOENT;
    }
}

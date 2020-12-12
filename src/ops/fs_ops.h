#pragma once

int fs_open(const char *, struct fuse_file_info *);
int fs_getattr(const char* file, struct stat* st, struct fuse_file_info* fi);

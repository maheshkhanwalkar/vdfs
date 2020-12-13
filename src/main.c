#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum cmd_type {
  MOUNT,
  UNMOUNT
} cmd_type_t;

typedef struct cmd {
    cmd_type_t type;
    const char** args;
    size_t arg_count;
} cmd_t;

__attribute__((noreturn))
static void die(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    vfprintf(stderr, msg, args);
    exit(1);
}

static cmd_t* prep(int argc, const char** argv)
{
    const char* type = argv[1];
    cmd_t* cmd = calloc(1, sizeof(*cmd));

    if(strcmp("mount", type) == 0) {
        cmd->type = MOUNT;

        if(argc != 4) {
            free(cmd);
            die("mount: bad args. expected: vdfs mount disk.img /where/to/mount");
        }

        cmd->arg_count = 2;
        cmd->args = &argv[2];
    }
    else if(strcmp("umount", type) == 0) {
        cmd->type = UNMOUNT;

        if(argc != 3) {
            free(cmd);
            die("umount: bad args. expected: vdfs umount /mount/point");
        }

        cmd->arg_count = 1;
        cmd->args = &argv[2];
    }
    else {
        free(cmd);
        die("unknown command: %s", type);
    }

    return cmd;
}

static void exec(cmd_t* cmd)
{
    // TODO
    free(cmd);
}

int main(int argc, const char* argv[])
{
    // Not enough arguments
    if(argc < 2) {
        die("error. expected format: vdfs [command type] [options]");
    }

    cmd_t* cmd = prep(argc, argv);
    exec(cmd);
}
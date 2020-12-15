#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x);
#define SECTOR_SIZE 512

typedef struct part {
    uint64_t start;
    uint64_t end;
} part_t;

typedef bool (*reader)(uint64_t sector, FILE* fp, char* buffer);
typedef bool (*writer)(uint64_t sector, FILE* fp, char* buffer);

void die(const char* msg, ...)__attribute__((noreturn));

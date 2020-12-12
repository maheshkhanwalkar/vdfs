#pragma once
#include <cstdio>
#include <cstdint>

/**
 * File handler abstraction
 *
 * The classes that extend this abstract class provide implementations of read()
 * and write() methods, which transform raw rw I/O into the required format for the
 * underlying disk image.
 */
class handler
{
public:
    /**
     * Initialise a new handler with the provided underlying file pointer
     * @param fp file pointer
     */
    explicit handler(FILE* fp): fp(fp) { }

    /**
     * Check whether the given partition is valid
     * @param part partition number
     * @return true if in range, false otherwise
     */
    virtual bool is_valid(int part) = 0;

    /**
     * Read the specified amount of bytes into the buffer
     * @param part partition number
     * @param buffer byte buffer
     * @param amt amount of bytes to read
     * @param pos starting byte position in the file
     * @return -1 on error, # of bytes read otherwise
     */
    virtual int read(int part, char* buffer, uint64_t amt, uint64_t pos) = 0;

    /**
     * Write the specified amount of bytes from the buffer
     * @param part partition number
     * @param buffer byte buffer
     * @param amt amount of bytes to write
     * @param pos starting byte position in the file
     * @return -1 on error, # of bytes written otherwise
     */
    virtual int write(int part, char* buffer, uint64_t amt, uint64_t pos) = 0;

    /**
     * Destroy the underlying file pointer
     */
    virtual ~handler() {
        fclose(fp);
    }

protected:
    FILE* fp;
};


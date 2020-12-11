#pragma once
#include <cstdio>

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
     * Read the specified amount of bytes into the buffer
     * @param buffer byte buffer
     * @param amt amount of bytes to read
     * @param pos starting byte position in the file
     * @return -1 on error, # of bytes read otherwise
     */
    virtual int read(char* buffer, int amt, int pos) = 0;

    /**
     * Write the specified amount of bytes from the buffer
     * @param buffer byte buffer
     * @param amt amount of bytes to write
     * @param pos starting byte position in the file
     * @return -1 on error, # of bytes written otherwise
     */
    virtual int write(char* buffer, int amt, int pos) = 0;

    /**
     * Destroy the underlying file pointer
     */
    virtual ~handler() {
        fclose(fp);
    }

protected:
    FILE* fp;
};


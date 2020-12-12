#pragma once
#include "disk/handler.h"

/**
 * Peek the file and detect the appropriate handler
 * @param fp pointer to the file to peek
 * @return the appropriate handler, or nullptr if the disk format is not recognised
 */
handler* find_handler(FILE* fp);

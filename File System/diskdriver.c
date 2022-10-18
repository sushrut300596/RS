#include "diskdriver.h"

void writeBlock(char *buffer, int block_no) {
    lseek(d, (block_no * block_size), SEEK_SET);
    write(d, buffer, block_size);
}

void readBlock(char *buffer, int block_no) {
    lseek(d, (block_no * block_size), SEEK_SET);
    read(d, buffer, block_size);
}
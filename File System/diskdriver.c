#include "diskdriver.h"

int get_block_size(char *diskname) {
    d = open(diskname, O_RDONLY);
    SB *sb = (SB *)malloc(sizeof(struct SB));
    read(d, sb, sizeof(struct SB));
    close(d);
    return sb->size_block;
}

void writeBlock(char *diskname, char *buffer, int block_no) {
    int block_size = get_block_size(diskname);
    lseek(d, (block_no * block_size), SEEK_SET);
    write(d, buffer, block_size);
}

void readBlock(char *diskname, char *buffer, int block_no) {
    int block_size = get_block_size(diskname);
    lseek(d, (block_no * block_size), SEEK_SET);
    read(d, buffer, block_size);
}
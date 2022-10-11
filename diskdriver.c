#include <stdio.h>
#include "diskdriver.h"

void writeBlock(char *buf, int block_no) {
	lseek(d, (block_no * block_size), SEEK_SET);
    write(d, buf, block_size);
}

void readBlock(char *buf, int block_no) {
	lseek(d, (block_no * block_size), SEEK_SET);
    read(d, buf, block_size);	
}
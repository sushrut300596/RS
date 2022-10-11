#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "bitmap.h"

unsigned char *bitmap_to_array(SB *sb) {
    // printf("%ld\n", sb->size_bitmap);
    unsigned char *bmap = (unsigned char *)malloc(sizeof(unsigned char) * sb->size_bitmap); 
    lseek(d, sizeof(SB), SEEK_SET);
    int n;
    int i = 0;
    int count = 0;
    n = read(d, bmap, sb->size_bitmap);
    return bmap;
}

int find_empty_blocks(unsigned char *bmap, SB *sb) {
    int i = 0;
    int j = 0;
    unsigned char bit = 0x01;
    int free_blocks = 0;
    while(i < sb->size_bitmap) {
        unsigned char ch = bmap[i];
        while(j < 8) {
            if(ch & bit) {
                free_blocks++;
            }
            ch >>= 1;
            j++;
        }
        j = 0;
        i++;
    }
    // printf("%d\n", free_blocks);
    return free_blocks;
}

int find_first_empty_block(int free_blocks, SB *sb) {
    return ((sb->size_bitmap * 8) - free_blocks);
}

void set_bitmap(unsigned char *bmap, int no_blocks) {
    int i = 0;
    while(no_blocks >= 0) {
        if(no_blocks >= 8) {
            bmap[i] >>= 8;
        }
        else {
            bmap[i] >>= no_blocks;
        }
        i++;
        no_blocks -= 8;
    }
}

/*int main() {
    SB *sb = malloc(sizeof(SB));
    d = open("disk", O_RDWR);
    read(d, sb, sizeof(SB));
    unsigned char *bmap = bitmap_to_array(sb);
    int free_blocks = find_empty_blocks(bmap, sb);
    int block_no = find_first_empty_block(free_blocks, sb);
    printf("%d\n", block_no);
    int i = 0;
    while(i < sb->size_bitmap) {
        printf("%02x\t", bmap[i]);
        i++;
    }
    printf("\n");
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "bitmap.h"

unsigned char *bitmap_to_array(SB *sb) {
    printf("%ld\n", sb->size_bitmap);
    unsigned char *bmap = (unsigned char *)malloc(sizeof(unsigned char) * sb->size_bitmap); 
    lseek(d, sizeof(SB), SEEK_SET);
    int n;
    int i = 0;
    int count = 0;
    n = read(d, bmap, sb->size_bitmap);
    return bmap;
}

void find_empty_blocks(unsigned char *bmap, SB *sb) {
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
    printf("%d\n", free_blocks);
}

void set_bitmap(unsigned char *bmap) {

}

int main() {
    SB *sb = malloc(sizeof(SB));
    d = open("disk", O_RDWR);
    read(d, sb, sizeof(SB));
    unsigned char *bmap = bitmap_to_array(sb);
    find_empty_blocks(bmap, sb);
    // int i = 0;
    // while(i < sb->size_bitmap) {
    //     printf("%02x\t", bmap[i]);
    //     i++;
    // }
    // printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "vdc.h"
#include "bitmap.h"

unsigned char *bitmap_to_array(char *diskname) {
    SB *sb = malloc(sizeof(SB));
    unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    d = open(diskname, O_RDWR);
    size_bitmap = sb->size_bitmap;
    unsigned char *bmap = malloc(size_bitmap);
    lseek(d, sizeof(sb), SEEK_SET);
    int n;
    int i = 0;
    int count = 0;
    while(count < size_bitmap) {
        n = read(d, buf, size_bitmap);
        bmap[i] = buf[i];
        i++;
        count = count + n;
    }
    return bmap;
}

void set_bitmap(unsigned char *bmap) {

}
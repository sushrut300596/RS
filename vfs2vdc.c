#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "math.h"

// #define SIZE 4294967296
// #define SIZE 1024
// #define SIZE 1024*1024

typedef struct SB{
	long size_disk;
	int size_block;
} SB;

void vdCreate(char *filename, int size, char b) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	if(b == 'M') {
		sb->size_disk = size*1024*1024;
	}
	if(b == 'G') {
		sb->size_disk = size*1024*1024*1024;
	}
	sb->size_block = 1024;
	double no_blocks = my_ceil(sb->size_disk/sb->size_block);
	double md_bytes = my_ceil(no_blocks/8);
	int sb_size = sizeof(struct SB);
	double flag_bytes = md_bytes;
	double no_blocks_flags;
	int buf_size = md_bytes;
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
	int d;
	char ch = '\0';
	d = open(filename, O_CREAT | O_WRONLY, 00700);
	lseek(d, sb->size_disk, SEEK_SET);
	write(d, &ch, 1);
	lseek(d, 0, SEEK_SET);
	int n;
	int i = 0;
	while(i < sizeof(struct SB)) {
		buf[i] = ((char *)sb)[i];
		i++;
	}
	n = write(d, buf, sizeof(struct SB));
	if(flag_bytes > 1024) {
		no_blocks_flags = my_ceil(flag_bytes/sb->size_block);
	}
	else if(flag_bytes < 1024) {
		no_blocks_flags = 1;
	}
	else {
		no_blocks_flags = 2;
	}
	i = 0;
	while(i < flag_bytes) {
		buf[i] = 0xff;
		i++;
	}
	printf("no_blocks_flags : %d\n", (int)no_blocks_flags);
	i = 0;
	while(no_blocks_flags >= 0) {
		buf[i] >>= (int)no_blocks_flags;
		i++;
		no_blocks_flags -= 8;
	}
	n = write(d, buf, flag_bytes);
	close(d);
	printf("size_disk : %ld\n", sb->size_disk);
	printf("no_blocks : %f\n", no_blocks);
	printf("md_bytes : %f\n", md_bytes);
	printf("sb_size : %d\n", sb_size);
	printf("flag_bytes : %f\n", flag_bytes);
}

int main(int argc, char **argv) {
	if(argv[3][0] == 'M') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	else if(argv[3][0] == 'G') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	// vdCreate(argv[1]);
}
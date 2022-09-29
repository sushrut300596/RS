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
	long size_fmd;
} SB;

typedef struct FMD {
	char file_name[248];
	int file_size;
	int block_no;
} FMD;

typedef union header {
	FMD fmd;
	struct {
		union header *next;
	}s;
} Header;

void vdCreate(char *diskname, int size, char b) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	if(b == 'M') {
		if(size < 1) {
			printf("cannot give that low disk\n");
		}
		else {
			sb->size_disk = size * 1024 * 1024;
		}
	}
	if(b == 'G') {
		if(size > 4) {
			printf("cannot give that much disk\n");
		}
		else {
			sb->size_disk = size * 1024 * 1024 *1024;
		}
	}
	
	sb->size_block = 1024;

	int no_bit_move = 0;

	sb->size_fmd = my_ceil((double)sb->size_disk/100)*3;
	printf("size_fmd : %ld\n", sb->size_fmd);
	int no_blocks_fmd = my_ceil((double)sb->size_fmd/sb->size_block);

	printf("no_blocks_fmd : %d\n", no_blocks_fmd);

	no_bit_move += no_blocks_fmd;

	int no_blocks = my_ceil((double)sb->size_disk/sb->size_block);
	int md_bytes = my_ceil((double)no_blocks/8);
	int sb_size = sizeof(struct SB);
	
	int flag_bytes = md_bytes;
	int no_blocks_flags;
	
	int buf_size = 1024 * 1024;
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
	
	int d;
	char ch = '#';
	
	d = open(diskname, O_CREAT | O_WRONLY, 00700);
	lseek(d, sb->size_disk, SEEK_SET);
	
	write(d, &ch, 1);
	
	lseek(d, 0, SEEK_SET);
	
	int n;
	
	int i = 0;
	while(i < sb_size) {
		buf[i] = ((char *)sb)[i];
		i++;
	}
	
	n = write(d, buf, sb_size);
	
	if(flag_bytes > 1024) {
		no_blocks_flags = my_ceil((double)flag_bytes/sb->size_block);
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

	printf("no_blocks_flags : %d\n", no_blocks_flags);
	
	no_bit_move += no_blocks_flags;

	printf("no_bit_move : %d\n", no_bit_move);
	
	i = 0;
	while(no_bit_move >= 0) {
		if(no_bit_move >= 8) {
			buf[i] >>= 8;
		}
		else {
			buf[i] >>= no_bit_move;
		}
		i++;
		no_bit_move -= 8;
	}
	
	n = write(d, buf, flag_bytes);
	
	printf("size_disk : %ld\n", sb->size_disk);
	printf("no_blocks : %d\n", no_blocks);
	printf("md_bytes : %d\n", md_bytes);
	printf("sb_size : %d\n", sb_size);
	printf("flag_bytes : %d\n", flag_bytes);
}

int main(int argc, char **argv) {
	// printf("%ld\n", sizeof(Header));
	// exit(1);

	if(argv[3][0] == 'M') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	else if(argv[3][0] == 'G') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
}
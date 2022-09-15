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
	int size_fmd;
} SB;

typedef struct FMD {
	char filename[238];
	int file_size;
	int *fp;
} FMD;

typedef union header {
	FMD fmd;
	struct {
		union header *next;
	} node;
} Header;



void vdCreate(char *filename, int size, char b) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	if(b == 'M') {
		sb->size_disk = size*1024*1024;
	}
	if(b == 'G') {
		sb->size_disk = size*1024*1024*1024;
	}
	
	sb->size_block = 1024;

	int no_bit_move = 0;

	sb->size_fmd = sb->size_disk/5;
	int no_blocks_fmd = my_ceil((double)sb->size_fmd/1024);

	printf("no_blocks_fmd : %d\n", no_blocks_fmd);

	no_bit_move += no_blocks_fmd;

	int no_blocks = my_ceil((double)sb->size_disk/sb->size_block);
	int md_bytes = my_ceil((double)no_blocks/8);
	int sb_size = sizeof(struct SB);
	
	int flag_bytes = md_bytes;
	int no_blocks_flags;
	
	int buf_size = 1024*1024;
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
	
	int d;
	char ch = '\0';
	
	d = open(filename, O_CREAT | O_WRONLY, 00700);
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

	/*i = 0;
	while(i < flag_bytes) {
		printf("%x", buf[i]);
		i++;
	}
	printf("\n");*/

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

	/*i = 0;
	while(i < flag_bytes) {
		printf("%x", buf[i]);
		i++;
	}
	printf("\n");*/
	
	n = write(d, buf, flag_bytes);
	close(d);
	
	printf("size_disk : %ld\n", sb->size_disk);
	printf("no_blocks : %d\n", no_blocks);
	printf("md_bytes : %d\n", md_bytes);
	printf("sb_size : %d\n", sb_size);
	printf("flag_bytes : %d\n", flag_bytes);
}

int main(int argc, char **argv) {
	// printf("%ld\n", sizeof(SB));
	// exit(1);

	if(argv[3][0] == 'M') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	else if(argv[3][0] == 'G') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	// vdCreate(argv[1]);
}
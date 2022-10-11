#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "math.h"
#include "vdc.h"

// #define SIZE 4294967296
// #define SIZE 1024
// #define SIZE 1024*1024

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
	sb->no_files = my_ceil((double)sb->size_fmd/256);
	printf("size_fmd : %ld\n", sb->size_fmd);
	printf("no_files : %d\n", sb->no_files);
	int no_blocks_fmd = my_ceil((double)sb->size_fmd/sb->size_block);

	printf("no_blocks_fmd : %d\n", no_blocks_fmd);

	no_bit_move += no_blocks_fmd;

	int no_blocks = my_ceil((double)sb->size_disk/sb->size_block);
	int sb_size = sizeof(struct SB);
	int md_bytes = (my_ceil((double)no_blocks/8)) + sb_size;
	
	
	int flag_bytes = md_bytes - sb_size;
	sb->size_bitmap = flag_bytes;
	int no_blocks_flags;
	
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
	
	int d;
	char ch = '#';
	
	d = open(diskname, O_CREAT | O_WRONLY, 00700);
	lseek(d, sb->size_disk, SEEK_SET);
	
	write(d, &ch, 1);
	
	lseek(d, 0, SEEK_SET);
	
	int n;
	
	int i = 0;
	// while(i < sb_size) {
	// 	buf[i] = ((char *)sb)[i];
	// 	i++;
	// }
	
	n = write(d, sb, sb_size);
	
	if(sb->size_bitmap > sb->size_block) {
		no_blocks_flags = (my_ceil((double)sb->size_bitmap/sb->size_block));
	}
	else if(sb->size_bitmap < sb->size_block) {
		no_blocks_flags = 1;
	}
	else {
		no_blocks_flags = 2;
	}

	i = 0;
	while(i < sb->size_bitmap) {
		buf[i] = 0xff;
		i++;
	}

	printf("no_blocks_flags : %d\n", no_blocks_flags);
	
	no_bit_move += (no_blocks_flags + 1);

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

	lseek(d, sb->size_block, SEEK_SET);
	
	n = write(d, buf, sb->size_bitmap);

	printf("size_disk : %ld\n", sb->size_disk);
	printf("no_blocks : %d\n", no_blocks);
	printf("md_bytes : %d\n", md_bytes);
	printf("sb_size : %d\n", sb_size);
	printf("flag_bytes : %ld\n", sb->size_bitmap);
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
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

// #define SIZE 4294967296
// #define SIZE 1024
// #define SIZE 1024*1024

typedef struct SB{
	long size_disk;
	int size_block;
} SB;

void vdCreate(char *filename, int size, char b) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	sb->size_disk = size*1024*1024;
	sb->size_block = 1024;
	double no_blocks = sb->size_disk/sb->size_block;
	double md_bytes = no_blocks/8;
	double no_blocks_md = ceil(md_bytes/8);
	double flag_bytes_md = ceil(no_blocks_md/8);
	// int sb_size = sizeof(struct SB);
	double flag_bytes = md_bytes - flag_bytes_md;
	double buf_size = md_bytes;
	char *buf = (char *)malloc(sizeof(char) * buf_size);
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
	i = 0;
	while(i < flag_bytes) {
		buf[i] = 0xff;
		i++;
	}
	n = write(d, buf, flag_bytes);
	close(d);
	printf("size : %ld\n", sb->size_disk);
	printf("no_blocks : %f\n", no_blocks);
	printf("md_bytes : %f\n", md_bytes);
	printf("no_blocks_md : %f\n", no_blocks_md);
	printf("flag_bytes_md : %f\n", flag_bytes_md);
	// printf("sb_size : %d\n", sb_size);
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
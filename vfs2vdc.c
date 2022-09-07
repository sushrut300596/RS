#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

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
	int no_blocks = sb->size_disk/sb->size_block;
	int md_bytes = no_blocks/8;
	int sb_size = md_bytes/8;
	int flag_bytes = md_bytes - sb_size;
	int buf_size = md_bytes;
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
	n = write(d, buf, sb_size);
	i = 0;
	while(i < flag_bytes) {
		buf[i] = 0xff;
		i++;
	}
	n = write(d, buf, flag_bytes);
	close(d);
}

int main(int argc, char **argv) {
	// if(argv[3][0] == 'K') {
	// 	vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	// }
	if(argv[3][0] == 'M') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	else if(argv[3][0] == 'G') {
		vdCreate(argv[1], atoi(argv[2]), argv[3][0]);
	}
	// vdCreate(argv[1]);
}
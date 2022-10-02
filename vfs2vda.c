#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "math.h"
#include "bitmap.c"

#define BUF_SIZE 1024
#define FILE_SIZE_MULTIPLE 1024

typedef struct FMD {
	char file_name[248];
	int file_size;
	int block_no;
} FMD;

void vdAllocate(char *diskname, char *filename) {
	FMD *fmd = malloc(sizeof(FMD));
	
	int d, fd;
	d = open(diskname, O_RDWR);
	fd = open(filename, O_RDONLY);
	
	int size = lseek(fd, 0, SEEK_END);
	if(size < (2 * FILE_SIZE_MULTIPLE * FILE_SIZE_MULTIPLE)) {
		fmd->file_size = size;
	}
	strcpy(fmd->file_name,filename);
	fmd->block_no = 64;

	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);
	unsigned char *read_buf = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);
	unsigned char *write_buf = (unsigned char *)malloc(sizeof(unsigned char) * BUF_SIZE);

	int n, i, count;

	lseek(d, 2048, SEEK_SET);
	write(d, fmd, sizeof(FMD));

	lseek(fd, 0, SEEK_SET);
	i = 0;
	count = 0;
	while(count < fmd->file_size) {
		n = read(fd, buf, BUF_SIZE);
		while(i < BUF_SIZE) {
			if(i == (BUF_SIZE - 1)) {
				read_buf = realloc(read_buf, BUF_SIZE);
			}
			read_buf[i] = buf[i];
			i++;
		}
		count = count + n;
	}
	
	lseek(d, 62916, SEEK_SET);
	i = 0;
	count = 0;
	while(count < fmd->file_size) {
		while(i < BUF_SIZE) {
			write_buf[i] = read_buf[i];
			i++;
		}
		n = write(d, write_buf, BUF_SIZE);
		count = count + n;
	}
	
	lseek(d, 32, SEEK_SET);
	read(d, buf, 224);
	
	int no_blocks = my_ceil((double)fmd->file_size/BUF_SIZE);
	printf("%d\n", no_blocks);

	i = 0;
	while(no_blocks >= 0) {
		if(no_blocks >= 8) {
			buf[i] >>= 8;
		}
		else {
			buf[i] >>= no_blocks;
		}
		i++;
		no_blocks -= 8;
	}

	lseek(d, 32, SEEK_SET);
	write(d, buf, 224);
	
	close(d);
}

int main(int argc, char **argv) {
    // printf("%ld\n", sizeof(FMD));
    // exit(1);

	vdAllocate(argv[1], argv[2]);   
}
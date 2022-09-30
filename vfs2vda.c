#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "math.h"

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

Header base;
Header *freep = NULL;

void vdAllocate(char *diskname, char *filename, int size, char b) {
	Header *head = malloc(sizeof(Header));
	int d, fd;
	d = open(diskname, O_RDWR);
	fd = open(filename, O_RDONLY);
	if(b == 'M') {
		head->fmd.file_size = size * 1024 * 1024;
	}
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * head->fmd.file_size);
	int n;
	read(fd, buf, head->fmd.file_size);
	lseek(d, 62916, SEEK_SET);
	write(d, buf, head->fmd.file_size);
	lseek(d, 25, SEEK_SET);
	read(d, buf, 256);
	int no_blocks = my_ceil((double)head->fmd.file_size/1024);
	printf("%d\n", no_blocks);
	int i = 0;
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
	lseek(d, 25, SEEK_SET);
	write(d, buf, 256);
	close(d);
}

int main(int argc, char **argv) {
    // printf("%ld\n", sizeof(Header));
    // exit(1);

	vdAllocate(argv[1], argv[2], atoi(argv[3]), argv[4][0]);   
}
#include <stdio.h>
#include <string.h>
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

void vdAllocate(char *diskname, char *filename) {
	Header *head = malloc(sizeof(Header));
	
	int d, fd;
	d = open(diskname, O_RDWR);
	fd = open(filename, O_RDONLY);
	
	int size = lseek(fd, 0, SEEK_END);
	if(size < (2 * 1024 * 1024)) {
		head->fmd.file_size = size;
	}
	strcpy(head->fmd.file_name,filename);
	head->fmd.block_no = 63;
	
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * head->fmd.file_size);
	unsigned char *write_buf = (unsigned char *)malloc(sizeof(unsigned char) * 1024);
	
	int n;
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, head->fmd.file_size);
	lseek(d, 62916, SEEK_SET);
	int i = 0;
	int count = 0;
	while(count < head->fmd.file_size) {
		while(i < 1024) {
			write_buf[i] = buf[i];
			i++;
		}
		n = write(d, write_buf, 1024);
		count = count + n;
	}
	
	lseek(d, 31, SEEK_SET);
	read(d, buf, 224);
	
	int no_blocks = my_ceil((double)head->fmd.file_size/1024);
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
	lseek(d, 31, SEEK_SET);
	write(d, buf, 224);
	close(d);
}

int main(int argc, char **argv) {
    // printf("%ld\n", sizeof(Header));
    // exit(1);

	vdAllocate(argv[1], argv[2]);   
}
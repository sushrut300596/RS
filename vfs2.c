#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

// #define SIZE 4294967296
#define SIZE 1024

typedef struct SB{
	int size_disk;
	int size_block;
} SB;

void writeFile(char *filename) {
	int fd;
	int buf_size = 8;
	void *buf = (void *)malloc(sizeof(void) * buf_size);
	fd = open(filename, O_CREAT | O_WRONLY, 00700);
	int n, count = 0;
	int i = 0;
	while(count != SIZE) {
		while(i < buf_size) {
			// code
		}
		n = write(fd, buf, buf_size);
		count = count + n;
	}
	close(fd);
}

void readFile(char *filename) {
	int buf_size = 8;
	void *buf = (void *)malloc(sizeof(void) * buf_size);
	int fd;
	fd = open(filename, O_RDONLY);
	int i = 0;
	int n, count = 0;
	while(count != SIZE) {
		n = read(fd, buf, buf_size);
		while(i < buf_size) {
			// code
		}
		count = count + n;
	}
	close(fd);	
}

void vdCreate(char *filename) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	sb->size_disk = SIZE;
	sb->size_block = sb->size_disk/sb->size_disk;
	int buf_size = 8;
	void *buf = (void *)malloc(sizeof(void) * buf_size);
	int d;
	char ch = '\0';
	d = open(filename, O_CREAT | O_WRONLY, 00700);
	lseek(d, sb->size_disk, SEEK_SET);
	write(d, &ch, 1);
	lseek(d, 0, SEEK_SET);
	int i = 0;
	int n, count = 0;
	if(count == sb->size_disk) {
		printf("ERROR : Disk size is not available\n");
	}
	else {
		while(count != sb->size_disk) {
			while(i < buf_size) {
				
			}
			n = write(d, buf, buf_size)
			count = count + n;
		}
	}
	close(d);
}

int main(int argc, char **argv) {
	vdCreate(argv[1]);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>

// #define SIZE 4294967296
// #define SIZE 1024
#define SIZE 1024*1024

typedef struct SB{
	long size_disk;
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
	while(i < sb_size) {
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
	vdCreate(argv[1]);
}
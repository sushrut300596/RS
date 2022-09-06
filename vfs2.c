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

void vdCreate(char *filename) {
	SB *sb = (SB *)malloc(sizeof(struct SB));
	sb->size_disk = SIZE;
	sb->size_block = sb->size_disk/sb->size_disk;
	int d;
	char ch = '\0';
	d = open(filename, O_CREAT | O_WRONLY, 00700);
	lseek(d, sb->size_disk, SEEK_SET);
	write(d, &ch, 1);
	lseek(d, 0, SEEK_SET);

	close(d);
}

int main(int argc, char **argv) {
	vdCreate(argv[1]);
}
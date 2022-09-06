#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

// #define SIZE 4294967296
#define SIZE 1024

typedef struct SB{
	unsigned char size_disk;
	unsigned char size_MD;
} SB;

void vdCreate(char *filename) {
	int d;
	char ch = '\0';
	d = open(filename, O_CREAT | O_WRONLY, 00700);
	lseek(d, SIZE, SEEK_SET);
	write(d, &ch, 1);
	
	close(d);
}

int main(int argc, char **argv) {
	vdCreate(argv[1]);
}
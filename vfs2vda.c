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



void vdAllocate(char *diskname) {
	int d;
	
}

int main(int argc, char **argv) {
    printf("%ld\n", sizeof(Header));
    exit(1);   
}
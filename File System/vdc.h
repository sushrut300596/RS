#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

typedef struct SB{
	long size_disk;
	int size_block;
} SB;

typedef struct FMD {
	char file_name[240];
	long file_size;
	int block_no;
	unsigned char b;
} FMD;
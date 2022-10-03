#include "bitmap.c"
#include "vdc.h"

typedef struct FMD {
	char file_name[248];
	int file_size;
	int block_no;
} FMD;

int d;

int fd;

int add_file(char*, char*, SB*, FMD*);
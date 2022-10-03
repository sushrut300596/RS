#include "bitmap.c"

typedef struct FMD {
	char file_name[244];
	int file_size;
	int block_no;
	int b;
} FMD;

int d;

int fd;

int add_file(char*, char*, SB*, FMD*, int);
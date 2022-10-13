typedef struct SB{
	long size_disk;
	int size_block;
} SB;

typedef struct FMD {
	char file_name[244];
	int file_size;
	int block_no;
	int b;
} FMD;
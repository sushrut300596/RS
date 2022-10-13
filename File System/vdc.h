typedef struct SB{
	long size_disk;
	int size_block;
} SB;

typedef struct FMD {
	char file_name[244];
	long file_size;
	int block_no;
	unsigned char b;
} FMD;
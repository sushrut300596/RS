typedef struct SB{
	long size_disk;
	int size_block;
} SB;

typedef struct FMD {
	char file_name[243];
	long file_size;
	int block_no;
	unsigned char b;
} FMD;
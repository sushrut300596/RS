typedef struct SB{
	long size_disk;
	int size_block;
	long size_fmd;
	long size_bitmap;
	int no_files;
} SB;

int buf_size = 1024;
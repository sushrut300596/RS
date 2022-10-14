#include "vdc.h"

void vdCreate(char *diskname, int size_disk, char bytes_disk, int size_block, char bytes_block) {
	SB *sb = (SB *)malloc(sizeof(struct SB));

	int d;
	char ch = '#';

	if(bytes_disk == 'M') {
		if(size_disk < 512) {
			printf("cannot give that low disk\n");
		}
		else {
			sb->size_disk = size_disk * 1024 * 1024;
			if(bytes_block == 'B') {
				if(size_block < 512) {
					printf("cannot give that low block size\n");
				}
				else {
					sb->size_block = size_block;
				}
			}
			if(bytes_block == 'K') {
				if(size_block > 16) {
					printf("cannot give that much block size\n");
				}
				else {
					sb->size_block = size_block * 1024;
				}
			}
			d = open(diskname, O_CREAT | O_WRONLY, 00700);
			lseek(d, sb->size_disk - 1, SEEK_SET);
			write(d, &ch, 1);
		}
	}

	if(bytes_disk == 'G') {
		if(size_disk > 10) {
			printf("cannot give that much disk\n");
		}
		else {
			sb->size_disk = size_disk * 1024 * 1024 *1024;
			if(bytes_block == 'B') {
				if(size_block < 512) {
					printf("cannot give that low block size\n");
				}
				else {
					sb->size_block = size_block;
				}
			}
			if(bytes_block == 'K') {
				if(size_block > 16) {
					printf("cannot give that much block size\n");
				}
				else {
					sb->size_block = size_block * 1024;
				}
			}
			d = open(diskname, O_CREAT | O_WRONLY, 00700);
			lseek(d, sb->size_disk - 1, SEEK_SET);
			write(d, &ch, 1);
		}
	}

	int no_bit_move = 0;

	int size_fmd = ceil((double)sb->size_disk/100)*3;
	// printf("size_fmd : %d\n", size_fmd);

	int no_blocks_fmd = ceil((double)size_fmd/sb->size_block);
	// printf("no_blocks_fmd : %d\n", no_blocks_fmd);

	no_bit_move += no_blocks_fmd;

	int no_blocks = ceil((double)sb->size_disk/sb->size_block);
	int sb_size = sizeof(struct SB);
	int md_bytes = (ceil((double)no_blocks/8)) + sb_size;
	int flag_bytes = md_bytes - sb_size;
	int size_bitmap = flag_bytes;
	int no_blocks_flags;
	
	unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * sb->size_block);
	
	lseek(d, 0, SEEK_SET);
	
	int n;
	// while(i < sb_size) {
	// 	buf[i] = ((char *)sb)[i];
	// 	i++;
	// }
	
	n = write(d, sb, sb_size);
	
	if(size_bitmap > sb->size_block) {
		no_blocks_flags = (ceil((double)size_bitmap/sb->size_block));
	}
	else if(size_bitmap < sb->size_block) {
		no_blocks_flags = 1;
	}
	else {
		no_blocks_flags = 2;
	}

	int i = 0;
	while(i < size_bitmap) {
		buf[i] = 0xff;
		i++;
	}

	// printf("no_blocks_flags : %d\n", no_blocks_flags);
	
	no_bit_move += (no_blocks_flags + 1);

	// printf("no_bit_move : %d\n", no_bit_move);
	
	i = 0;
	while(no_bit_move >= 0) {
		if(no_bit_move >= 8) {
			buf[i] >>= 8;
		}
		else {
			buf[i] >>= no_bit_move;
		}
		i++;
		no_bit_move -= 8;
	}

	lseek(d, sb->size_block, SEEK_SET);
	
	n = write(d, buf, size_bitmap);

	

	// printf("size_disk : %ld\n", sb->size_disk);
	// printf("no_blocks : %d\n", no_blocks);
	// printf("md_bytes : %d\n", md_bytes);
	// printf("sb_size : %d\n", sb_size);
	// printf("flag_bytes : %d\n", size_bitmap);
}

int main(int argc, char **argv) {
	// printf("%ld\n", sizeof(FMD));
	// exit(1);
	vdCreate(argv[1], atoi(argv[2]), argv[3][0], atoi(argv[4]), argv[5][0]);
}
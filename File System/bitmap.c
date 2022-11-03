#include "bitmap.h"

unsigned char *Bitmap_to_Array(char *diskname) {
    d = open(diskname, O_RDONLY);
    
    int sb_size = sizeof(struct SB);

    SB *sb = (SB *)malloc(sb_size);

    read(d, sb, sb_size);

    int no_blocks = ceil((double)sb->size_disk/sb->size_block);
	int md_bytes = (ceil((double)no_blocks/8)) + sb_size;
	int flag_bytes = md_bytes - sb_size;
	int size_bitmap = flag_bytes;

    unsigned char *bmap = (unsigned char *)malloc(sizeof(unsigned char) * size_bitmap);

    lseek(d, sb->size_block, SEEK_SET);

    read(d, bmap, size_bitmap);

    return bmap;
}

int BitMap_isBitSet(unsigned char *bmap, int block_no) {
    int entry_no = block_no / 8;
    int bit_no = block_no % 8;
    unsigned char e = bmap[entry_no];
    int ret = (e) & (1 << (8 - 1 - bit_no));
    if(ret != 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int BitMap_getFreeBlocks(unsigned char *bmap, int size_bitmap) {
    int i;
    int count = 0;
    for(i = 0; i < size_bitmap; i++) {
        if(BitMap_isBitSet(bmap, i)) {
            count++;
        }
    }
    return count;
}


// int main(int argc, char **argv) {
//     d = open(argv[1], O_RDONLY);
    
//     int sb_size = sizeof(struct SB);

//     SB *sb = (SB *)malloc(sb_size);

//     read(d, sb, sb_size);

//     int no_blocks = ceil((double)sb->size_disk/sb->size_block);
// 	int md_bytes = (ceil((double)no_blocks/8)) + sb_size;
// 	int flag_bytes = md_bytes - sb_size;
// 	int size_bitmap = flag_bytes;

//     unsigned char *bmap = (unsigned char *)malloc(sizeof(unsigned char) * size_bitmap);

//     bmap = Bitmap_to_Array(argv[1]);
    
//     int free_blocks = BitMap_getFreeBlocks(bmap, size_bitmap);
//     printf("free_blocks : %d\n", free_blocks);
// }
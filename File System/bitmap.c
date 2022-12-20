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

/*BitMapEntryKey BitMap_blockToIndex(int num) {
    BitMapEntryKey entry_key;
    entry_key.entry_num = num / NUMBITS;
    entry_key.bit_num = num % NUMBITS;
    return entry_key;
    
}*/

/*int BitMap_indexToBlock(int entry, unsigned char bit_num) {
    int num = (entry * 8) + bit_num;
    return num;
}*/

int BitMap_check(unsigned char num, int status) {
    if (num < 0) {
        return ERROR_RESEARCH_FAULT;
    }
    int i = 7;
    while (i >= 0) {
        if (status != 0 && !(num & (1 << i))) {
            return (7 - i);           
        }
        else if (status == 0 && (num & (1 << i))) {
            return (7 - i);
        }   
    
        i--;
    }
    return ERROR_RESEARCH_FAULT;
}


int BitMap_get(unsigned char *bmap, int start, int status, int size_bitmap) {
    int i = start;
    while (i < size_bitmap) {
        int pos = BitMap_check(bmap[i], status);
        if (pos != ERROR_RESEARCH_FAULT) {
            return (i * NUMBITS + pos);
        }
        i++;
    }
    return ERROR_RESEARCH_FAULT;
}

int BitMap_set(unsigned char *bmap, int pos, int status) {
    int array_index = pos / 8;
    int offset = pos % 8;
    if (status) {
        return bmap[array_index] |= (status << (7 - offset));
    }
    else if (!status) {
        return bmap[array_index] &= ~(1 << (7 - offset));
    }
    else
        return ERROR_RESEARCH_FAULT;
}

int BitMap_isBitSet(unsigned char *bmap, int block_no) {
    int entry_no = block_no / 8;
    unsigned char bit_no = block_no % 8;
    unsigned char e = bmap[entry_no];
    int ret = (e) & (1 << (7 - bit_no));
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
    int total_bits = size_bitmap * 8;
    for(i = 0; i < total_bits; i++) {
        if(BitMap_isBitSet(bmap, i)) {
            count++;
        }
    }
    return count;
}


int main(int argc, char **argv) {
    d = open(argv[1], O_RDONLY);
    
    int sb_size = sizeof(struct SB);

    SB *sb = (SB *)malloc(sb_size);

    read(d, sb, sb_size);

    int no_blocks = ceil((double)sb->size_disk/sb->size_block);
	int md_bytes = (ceil((double)no_blocks/8)) + sb_size;
	int flag_bytes = md_bytes - sb_size;
	int size_bitmap = flag_bytes;

    unsigned char *bmap = (unsigned char *)malloc(sizeof(unsigned char) * size_bitmap);

    bmap = Bitmap_to_Array(argv[1]);
    
    int free_blocks = BitMap_getFreeBlocks(bmap, size_bitmap);

    printf("free_blocks : %d\n", free_blocks);

}
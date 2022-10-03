#include "vda.h"

int add_file(char *diskname, char *filename, SB *sb, FMD *fmd, int block_no) {
    int no_blocks_flags;
    static int no_files = 0;
    d = open(diskname, O_RDWR);
    fd = open(filename, O_RDONLY);
    fmd->file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    unsigned char *read_buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);

    if(sb->size_bitmap > sb->size_block) {
        no_blocks_flags = my_ceil((double)sb->size_bitmap/sb->size_block);
        lseek(d, ((no_blocks_flags * sb->size_block) + (no_files * sizeof(FMD))), SEEK_SET);
    }
    else if(sb->size_bitmap < sb->size_block) {
        lseek(d, (sb->size_block + (no_files * sizeof(FMD))), SEEK_SET);        
    }
    else {
        lseek(d, ((2 * sb->size_block) + (no_files * sizeof(FMD))), SEEK_SET);
    }
    
    strcpy(fmd->file_name, filename);
    fmd->block_no = block_no;
    fmd->b = 1;

    write(d, fmd, sizeof(FMD));
    
    no_files++;

    lseek(d, (block_no * sb->size_block), SEEK_SET);

    int n;
    int i = 0;
    int count = 0;
    while(count < fmd->file_size) {
        n = read(fd, buf, buf_size);
        while(i < buf_size) {
            read_buf[i] = buf[i];
            i++;
        }
        write(d, read_buf, buf_size);
        count = count + n;
    }
    return fmd->block_no;
}
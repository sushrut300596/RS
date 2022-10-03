#include "vda.h"

int add_file(char *diskname, char *filename, SB *sb, FMD *fmd, int block_no) {
    FMD *fmd1 = NULL;
    d = open(diskname, O_RDWR);
    fd = open(filename, O_RDONLY);
    fmd->file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    unsigned char *read_buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    int i = 0, j = 0;
    while(i < sb->size_fmd) {
        i = read(d, fmd1, sizeof(FMD));
        if((strcmp(fmd1->file_name, filename)) == 0) {
            printf("File is not inserted because file exist\n");
            break;
        }
        else {
            strcpy(fmd->file_name, filename);        
        }
        if(fmd1->b == 1) {
            if(fmd1->file_size >= fmd->file_size) {

            }
        }
        i += i;
    }
    
    
    fmd->block_no = block_no;
    lseek(d, (sb->size_bitmap * 4), SEEK_SET);
    write(d, fmd, sizeof(FMD));
    lseek(d, sb->size_fmd, SEEK_SET);
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
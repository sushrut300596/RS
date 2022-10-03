#include "vda.h"

int add_file(char *diskname, char *filename, SB *sb, FMD *fmd) {
    d = open(diskname, O_RDWR);
    fd = open(filename, O_RDONLY);
    unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    unsigned char *read_buf = (unsigned char *)malloc(sizeof(unsigned char) * buf_size);
    strcpy(fmd->file_name, filename);
    fmd->file_size = lseek(fd, 0, SEEK_END);
    int n;
    int i = 0;
    int count = 0;
    while(i < fmd->file_size) {
        n = read(fd, buf, buf_size);

    }
    read(d, sb, sizeof(SB));
    lseek(d, sb->size_bitmap, SEEK_SET);
    write(d, fmd, sizeof(FMD));
    lseek(d, sb->size_fmd, SEEK_SET);
}
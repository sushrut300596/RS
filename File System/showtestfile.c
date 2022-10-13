#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void showFile(char *filename, int start, int count) {
	int fd;
	fd = open(filename, O_RDONLY);
	lseek(fd, start, SEEK_SET);
	unsigned char *str = malloc(count * sizeof(char));
	int n;
	int i = 0, j = 0;
    int count0 = 0;
	if(fd != -1) {
		n = read(fd, str, count);
		while(i < n) {
			if(i % 8 == 0) {
				printf("\n");
			}
			else {
				printf("%02x\t", str[i]);
                if(str[i] == 0x00) {
                    count0++;
                }
			}
			i++;
		}
	}
	printf("\n");
    printf("%d\n", count0);
}

int main(int argc, char **argv) {
	showFile(argv[1], atoi(argv[2]), atoi(argv[3]));
}
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
	unsigned char *str = malloc(count * sizeof(char));
	int n;
	int i = 0, j = 0;
	if(fd != -1) {
		n = read(fd, str, count);
		while(i < n) {
			if(i % 8 == 0) {
				printf("\n");
			}
			else {
				printf("%x\t", str[i]);
			}
			i++;
		}
	}
	printf("\n");
}

int main(int argc, char **argv) {
	showFile(argv[1], atoi(argv[2]), atoi(argv[3]));
}
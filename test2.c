#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void readFile(int fd) {
	int i = 0, n, arrlength, strlength;
	unsigned char *str = malloc(5);
	if(fd != -1) {
    	n = read(fd, str, sizeof(int));
    	arrlength = *(int *)str;
    	printf("%d ", arrlength);
    	while(i < arrlength) {
    		n = read(fd, str, sizeof(int));
    		strlength = *(int *)str;
    		printf(" %d ", strlength);
       		n = read(fd, str, strlength);
    		printf("%s", str);
      		i++;
    	}
    	printf("\n");
  	}
}

int main() {
	char *str[4] = {"How ", "you ", "Doing", "!!"};
	int n = 4;
	int i;
	int fd;
	fd = open("char_test.txt", O_CREAT | O_WRONLY, 00700);
	write(fd, &n, sizeof(n));
	for(i = 0; i < n; i++) {
		int length = strlen(str[i]);
		write(fd, &length, sizeof(length));
		write(fd, str[i], length);
	}
	close(fd);
	fd = open("char_test.txt", O_RDONLY);
	readFile(fd);
	close(fd);
}
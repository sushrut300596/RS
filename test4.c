#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void readWrite(int fd, int fd1) {
	int i = 0, n, arrlength, count = 0;
	unsigned char *str = malloc(100);
	char *temp = malloc(50);
	if(fd != -1 && fd1 != -1) {
    	n = read(fd, str, sizeof(int));
    	arrlength =*(int *)str;
    	write(fd1, &arrlength, sizeof(int));
    	int strlength[arrlength];
    	while(i < arrlength) {
    		n = read(fd, str, sizeof(int));
    		strlength[i] = *(int *)str;
    		count = count + strlength[i];
       		n = read(fd, str, strlength[i]);
    		strcat(temp, str);
      		i++;
    	}
    	i = 0;
  		while(i < arrlength) {
    		write(fd1, &strlength[i], sizeof(int));
    		i++;
    	}
    	write(fd1, temp, count);
  	}
}

int main() {
	int fd, fd1;
	fd = open("char_test.txt", O_RDONLY);
	fd1 = open("char_test2.txt", O_CREAT | O_WRONLY, 00700);
	readWrite(fd, fd1);
	close(fd);
	close(fd1);
}
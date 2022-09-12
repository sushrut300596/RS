#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void writeFile(char *filename) {
	int fd;
	int buf_size = 8;
	void *buf = (void *)malloc(sizeof(void) * buf_size);
	fd = open(filename, O_CREAT | O_WRONLY, 00700);
	int n, count = 0;
	int i = 0;
	while(count != SIZE) {
		while(i < buf_size) {
			// code
		}
		n = write(fd, buf, buf_size);
		count = count + n;
	}
	close(fd);
}

void readFile(char *filename) {
	int buf_size = 8;
	void *buf = (void *)malloc(sizeof(void) * buf_size);
	int fd;
	fd = open(filename, O_RDONLY);
	int i = 0;
	int n, count = 0;
	while(count != SIZE) {
		n = read(fd, buf, buf_size);
		while(i < buf_size) {
			// code
		}
		count = count + n;
	}
	close(fd);	
}

void vdAllocate(char *filename) {
	int d;
	
}

int main(int argc, char **argv) {
    
}
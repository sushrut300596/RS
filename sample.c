#include <stdio.h>

int main() {
	char a = 0xff;
	a >>= 5;
	printf("%d\n", a);
}
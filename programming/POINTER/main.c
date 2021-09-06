#include <stdio.h>
int main(void) {
	int i;
	char *name[3] = {"apple", "ucos", "stm32"};
	char **ptr = name;
	for (i = 0; i < 3; i++) {
		printf("%s\n", *(name+i));
		printf("%s\n", ptr[i]);
		printf("%s\n", *(ptr+i));
		printf("%c\n", *(*(ptr+1)+2));
	}
	return 0;
}

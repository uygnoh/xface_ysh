#include "stdio.h"
#include "string.h"

int _write(int file, char *ptr, int len)
{
	int i = 0;
	for (i = 0; i < len; i++) {
		ITM_SendChar((*ptr++));
	}
	return len;
}

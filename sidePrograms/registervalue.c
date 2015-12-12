#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INT 32768

#define BUFFERSIZE (MAX_INT * MAX_INT)

int *buffer;

int reg;

int ackermann(int m, int n)
{
	int value = 0;
	int key = m*MAX_INT + n;

	if(buffer[key])
		return buffer[key];
	
	if(m == 0)
		value = n+1;
	else if(n == 0)
		value = ackermann(m-1,reg);
	else
		value = ackermann(m-1,ackermann(m,n-1));

	value %= MAX_INT;
	buffer[key] = value;
	return value;
}

int main()
{
	int r = -1;
	int value;

	buffer = (int *) malloc(BUFFERSIZE * sizeof(int));

	if(!buffer)
	{
		fprintf(stderr, "Could not allocate memory!\n");
		return 1;
	}

	for(reg = 0; reg < MAX_INT; ++reg)
	{
		memset(buffer, 0, BUFFERSIZE * sizeof(int));
		value = ackermann(4,1);
		if(value == 6) r = reg;
		printf("%d: %d\t\t%d\n", reg, value, r);
	}

	return 0;
}

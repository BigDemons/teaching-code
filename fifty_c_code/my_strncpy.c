/************************************************************************
    > File Name: my_strcpy.c
    > Author: peter
    > Mail: zpengwei@yeah.net 
    > Created Time: 六  5/ 7 13:03:34 2016
 ************************************************************************/
#include <string.h>
#include <stdio.h>
#include <assert.h>

char *my_strncpy(char *dest, const char *src, int count)
{
	char *ret = dest;
	assert(dest);
	assert(src);
	//拷贝过程，包含'\0'
	while(count-- && (*dest++ = *src++) != '\0')
	{
		;
	}
	if(count)
	{
		while(count--)
		{
			*dest++ = '\0';
		}
	}
	return ret;
}

int main()
{
		char arr[200] = {0};
		int i = 0;
		for(i = 0; i<100000000; i++)
			my_strncpy(arr, "hello bit.", 20);
		printf("%s\n",arr);
		return 0;
}

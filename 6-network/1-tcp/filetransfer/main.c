#include <stdio.h>
#include "md5.h"

int main(int argc, const char *argv[])
{
	char str[33];
	
	if (2 != argc) { 
		printf( "usage :\tmd5 <string>\n" ); 
		return -1; 
	} 
	
	file2md5(argv[1], str);
	puts(str);

	str2md5("helloworld", str);
	puts(str);
	
	return 0;
}

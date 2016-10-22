#include "md5.h"

int md5_str(const char *str, unsigned char *md5num)
{
	struct MD5Context md5c; 

	MD5_Init(&md5c); 
	MD5_Update(&md5c, (const unsigned char *)str, strlen(str)); 
	MD5_Final(md5num, &md5c); 

	return 0;
}

int md5_file(const char *fname, unsigned char *md5num)
{
	struct MD5Context md5c; 
	unsigned char databuf[BUFF_SIZE];
	int fd;
	int ret;

	if (-1 ==(fd = open(fname, O_RDONLY)))
		return -1;

	MD5_Init(&md5c); 

	while (1) {
		if (-1 == (ret = read(fd, databuf, BUFF_SIZE)))
			return -1;
		if (ret == 0)
			break;
		MD5_Update(&md5c, databuf, ret); 
	}
	close(fd);
	MD5_Final(md5num, &md5c); 

	return 0;
}

void md5_num2str(const unsigned char *md5num, char *md5str)
{
	char tmp[3]={'\0'}; 
	int i; 
	
	memset(md5str, 0, 17);
	for (i = 0; i < 16; i++ ) { 
		sprintf(tmp, "%02x", md5num[i]); 
		strcat(md5str, tmp); 
	}
}

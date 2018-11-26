#include "dong.h"

int arry_find(int arrynum[], int len)
{
	int curry;
	int i = 0, j = 0;
	
	/*冒泡排序法*/
	for (i=0; i< len; i++)
	{
		for (j = 0; j < len-1; j++) /*每次循环都是从0号位开始*/
		{
			if (arrynum[j] >  arrynum[j+1])
			{
				curry = arrynum[j];
				arrynum[j] = arrynum[j+1];
				arrynum[j+1] = curry;
			}
			
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int num[8]={23, 45, 76, 1,78, 1, 23, 46};
	int num_len = 0;
	int i;
	
	num_len = sizeof(num)/sizeof(int);
	
	
	arry_find(num, num_len);
	
	for (i = 0; i< num_len; i++)
	{
		printf("%d num:[%d]\n", i,num[i]);
	}
	
	return 0;
}

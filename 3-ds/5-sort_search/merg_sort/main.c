#include <stdio.h>
#include <stdlib.h>
#include "number.h"
#include <string.h>

int sort_bubble(int *data, int n);
int show(int *data, int n);
int compare(const void *value1, const void *value2);

int main()
{
	int i;
	int data[MAXNUM];
	
	puts("Original:");
	show(number, MAXNUM);
	putchar(10);

	for (i = 0; i < 100000; i++) {
		memcpy(data, number, sizeof(data));
		sort_merge(data, MAXNUM);
//		sort_bubble(data, MAXNUM);
//		qsort(data,MAXNUM,sizeof(int), compare);
//		myqsort(data, 0, MAXNUM);
	}

//	puts("Ordered:");
	show(data, MAXNUM);

	return 0;
}

int sort_bubble(int *data, int n)
{
	int i;
	int j;
	int tmp;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (data[j] > data[j+1]) {
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
			}	
		}
	}

	return 0;
}

int show(int *data, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%4d", data[i]);
		if (!((i+1) % 10))
			putchar('\n');
	}
	return 0;
}

int compare(const void *value1, const void *value2)
{
	return *(int *)value1 - *(int *)value2;
}

void swap(int *value1, int *value2)
{
	int tmp;
	if(value1 == value2)
		return ;

	tmp = *value1;
	*value1 = *value2;
	*value2 = tmp;
}

int partition(int arry[], int low, int high)
{
	int key = arry[low];

	while(low < high)
	{
		while(low < high && arry[high] >= key)
			high --;
		swap(arry+high, arry+low);

		while(low < high && arry[low] <= key)
			low ++;
		swap(arry+high, arry+low);
	}
	return low;
}

int myqsort(int *arry, int low, int high)
{
	int pivottag;

	if(low >= high)
		return 0;
	
	pivottag = partition(arry, low, high);
	myqsort(arry, low, pivottag-1);
	myqsort(arry, pivottag+1, high);

	return 0;
}

int merge(int *dest, int *src1, int *src2, int n)
{
	int i, j, k;
	
	for (i = 0, j = 0, k = 0; i < n && j < n; k++) {
		if (src1[i] <= src2[j])
			dest[k] = src1[i++];
		else
			dest[k] = src2[j++];
	}
	while (i < n)
		dest[k++] = src1[i++];
	while (j < n)
		dest[k++] = src2[j++];

	return 0;
}

int sort_merge(int *data, int max)
{
	int i;
	int tmp[MAXNUM];
	int n;
	int *dest;
	int *src1;
	int *src2;

	for (i = 0; i < 10; i++)
		sort_bubble(data + i * 10, 10);

#if 0
	puts("sort 10:");
	show(data, MAXNUM);
	putchar(10);
#endif
	
	n = 10;
	for (i = 0; i < 5; i++) {
		dest = tmp + 2 * n * i;
		src1 = data + 2 * n * i;
		src2 = data + 2 * n * i + n;
		merge(dest, src1, src2, n);
	}
	
//	show(tmp, MAXNUM);
//	putchar(10);

	n = 20;
	for (i = 0; i < 2; i++) {
		dest = data + 2 * n * i;
		src1 = tmp + 2 * n * i;
		src2 = tmp + 2 * n * i + n;
		merge(dest, src1, src2, n);
	}
	for (i = 80; i < MAXNUM; i++)
		data[i] = tmp[i];
	
//	show(data, MAXNUM);
//	putchar(10);

	n = 40;
	for (i = 0; i < 1; i++) {
		dest = tmp + 2 * n * i;
		src1 = data + 2 * n * i;
		src2 = data + 2 * n * i + n;
		merge(dest, src1, src2, n);
	}
//	show(tmp, MAXNUM);
//	putchar(10);

	int j, k;
	dest = data;
	src1 = tmp;
	src2 = tmp+80;
	for (i = 0, j = 0, k = 0; i < 80 && j < 20; k++) {
		if (src1[i] <= src2[j])
			dest[k] = src1[i++];
		else
			dest[k] = src2[j++];
	}
	while (i < 80)
		dest[k++] = src1[i++];
	while (j < 20)
		dest[k++] = src2[j++];

//	show(data, MAXNUM);

}

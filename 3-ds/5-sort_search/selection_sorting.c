#include <stdio.h>

#define N	10

int show(int *data, int n);
int selection(int *data, int n);

int main()
{
	int data[N] = {10,9,8,7,6,5,4,3,2,1};
	int i;

	show(data, N);
	selection(data, N);
	show(data, N);
	
	return 0;
}
	
int show(int *data, int n)
{
	int i;
	
	for (i = 0; i < n; i++)
		printf("%5d", data[i]);
	putchar(10);

	return 0;
}

int selection(int *data, int n)
{
	int i, j;
	int tmp;

#if 0
	int max;
	for (i = 0; i < n - 1; i++) {
		max = 0;
		for (j = 1; j < n - i; j++) {
			if (data[max] < data[j])
				max = j;
		}
		j--;
		tmp = data[j];	
		data[j] = data[max];
		data[max] = tmp;
	}
#else
	int min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i+1; j < n; j++) {
			if (data[min] > data[j])
				min = j;
		}
		tmp = data[i];
		data[i] = data[min];
		data[min] = tmp;
	}
#endif

	return 0;
}

#include <stdio.h>

#define N	10

int show(int *data, int n);
int bubble(int *data, int n);

int main()
{
	int data[N] = {10,9,8,7,6,5,4,3,2,1};
	int i;

	show(data, N);
	bubble(data, N);
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

int bubble(int *data, int n)
{
	int i, j;
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

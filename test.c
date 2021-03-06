#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#define N_PER_LINE 15
#define ARR_SIZE 100
void set_random(int arr[], int size)
{
	srand(time(0));
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % size;
	}
}

void show_array(int arr[], int size)
{
	int count;

	for (int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
		count++;
		if (count % N_PER_LINE == 0)
			putchar('\n');
	}
}
int main(void)
{
	int test[ARR_SIZE];
	set_random(test, ARR_SIZE);
	printf("Original: \n");
	show_array(test, ARR_SIZE);
	printf("\nkth: %d\n", Selection(test, ARR_SIZE, 10));
	Sort(test, ARR_SIZE, QUICK);
	printf("Sorted: \n");
	show_array(test, ARR_SIZE);

}
#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"


static void insertion(Item arr[], int size);
static void shell(Item arr[], int size);
static void error(const char * prompt)
{
	fprintf(stderr, "%s", prompt);
	exit(EXIT_FAILURE);
}
void Sort(Item arr[], int size, enum alg_type alg)
{
	switch(alg)
	{
		case INSERTION:	insertion(arr, size);
						break;
		case SHELL: shell(arr, size);
					break;
		default: error("Invalid alg_type.\n");
				break; 

	}
}

static void insertion(Item arr[], int size)
{
	int temp;
	int i, j;
	// We assume [0, i - 1] is sorted, and now make [0, i] sorted
	for (i = 1; i < size; ++i)
	{
		// temp is for holding the value to insert, because it will become the "hole"
		temp = arr[i];
		{
			// j always refer to the current hole, j != 0 is necessary
			for (j = i; j != 0 && arr[j - 1] > temp; j--)
			{
				arr[j] = arr[j - 1];
			}
		}
		arr[j] = temp;
	}

}

static void shell(Item arr[], int size)
{
	int increment;
	int temp;	
	int i, j;
	for (increment = size / 2; increment > 0; increment /= 2)
	{
		// i start from the second number of the first group, which is {0, increment, 2 * increment...}
		for (i = increment; i < size; i++)
		{
			temp = arr[i];
			// must be very careful to use arr[j - increment];
			// put j in group { j, j - increment, ... j - k * increment}
			// start from i; j > increment to ensure j >= 0 even after the loop;
			// arr[j - 1] > temp equals arr[j - 1] and arr[j] and in wrong position
			for (j = i; j > increment - 1 && arr[j - increment] > temp; j -= increment)
			{
				arr[j] = arr[j - increment];
			}
			arr[j] = temp;
		}		
	}
	
	
}






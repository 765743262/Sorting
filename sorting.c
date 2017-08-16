#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
// In qsort, if array size is less than or equal to CUTOFF, we consider it as a base case.
#define CUTOFF 20


static void insertion(Item arr[], int size);
static void shell(Item arr[], int size);
static void heap(Item arr[], int size);
static void merge(Item arr[], int size);
static void m_sort(Item arr[], Item temp[], int left, int right);
static void merge_two_array(Item arr[], Item temp[], int left, int right, int center);
static void quick(Item arr[], int size);
static int median_of_three(Item arr[], int left, int right);
static void q_sort(Item arr[], int left, int right);
static void error(const char * prompt)
{
	fprintf(stderr, "%s", prompt);
	exit(EXIT_FAILURE);
}
static inline void swap(Item a[], int i, int j) {int temp; temp = a[i]; a[i] = a[j]; a[j] = temp;}
void Sort(Item arr[], int size, enum alg_type alg)
{
	switch(alg)
	{
		case INSERTION:	insertion(arr, size);
						break;
		case SHELL: shell(arr, size);
					break;
		case HEAP: heap(arr, size);
					break;
		case MERGE: merge(arr, size);
					break;
		case QUICK: quick(arr, size);
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
	int max, temp;	
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

static void heap(Item arr[], int size)
{
	int temp;
	int max;
	int i, j;
	int child_index;
	
	for (j = (size - 1) / 2; j >= 0; j--)
	{
		temp = arr[j];
		for (i = j; i <= (size - 1) / 2; i = child_index)
		{
			child_index = i * 2 + 1;
			if ((child_index != size - 1) && (arr[child_index] < arr[child_index + 1]))
			{
				child_index++;
			}
			if (temp < arr[child_index])
				arr[i] = arr[child_index];
			else 
				break;
		}
		arr[i] = temp;
	}
	for (i = size - 1; i >= 0; i--)
	{
		max = arr[0];
		temp = arr[i];
		for (j = 0; j <= i / 2; j = child_index)
		{
			child_index = j * 2 + 1;
			if ((child_index != size - 1) && (arr[child_index] < arr[child_index + 1]))
			{
				child_index++;
			}
			if (temp < arr[child_index])
				arr[j] = arr[child_index];
			else
				break;
		}
		arr[j] = temp;
		arr[i] = max;
	}
	

}
// A driver to drive m_sort
static void merge(Item arr[], int size)
{
	int * temp;
	// create temperary array
	temp = (Item *) malloc(size * sizeof(int));
	if (temp == NULL)
		error("Malloc failed.\n");
	m_sort(arr, temp, 0, size - 1);
	free(temp);
}
// m_sort sort element between left and right in arr
static void m_sort(Item arr[], Item temp[], int left, int right)
{
	int center;
	int i;

	// printf("%d, %d\n", left, right);
		// printf("%d, ", arr[left]);	
	if (left < right)
	{
		center = (left + right) / 2;
		m_sort(arr, temp, left, center);
		m_sort(arr, temp, center + 1, right);
		// This merge the two array into temp
		merge_two_array(arr, temp, left, right, center);
		// !!! never forget to copy items back from temp
		for (i = left; i <= right; i++)
		{
			arr[i] = temp[i];
		}
	}
	// printf("%d\n", arr[left]);
	

}

static void merge_two_array(Item arr[], Item temp[], int left, int right, int center)
{
	// printf("%d\n", arr[left]);
	int index_l = left;
	int index_r = center + 1;
	int index_temp;

	for (index_temp = left; index_temp <= right; index_temp++)
	{
		// printf("%d\n", index_temp);
		if (index_l <= center && index_r <= right)
		{
			if (arr[index_l] < arr[index_r])
			{
				temp[index_temp] = arr[index_l++];
			}
			else
			{
				temp[index_temp] = arr[index_r++];
			}
		}
		else
		{	
			if (index_l <= center)
			{
				// printf("%d\n", arr[index_r]); 
				temp[index_temp] = arr[index_l++];
			}
			else
			{
				temp[index_temp] = arr[index_r++];
			}
		}
	}
}

static void quick(Item arr[], int size)
{
	q_sort(arr, 0, size - 1);
}

// This requires the array to contain as least three items.
static inline int median_of_three(Item arr[], int left, int right)
{
	int center = (left + right) / 2;
	if (arr[left] > arr[center])
		swap(arr, left, center);
	if (arr[center] > arr[right])
		swap(arr, center, right);
	if (arr[left] > arr[center])
		swap(arr, left, center);
	swap(arr, center, right - 1);

	return arr[right - 1];
}

static void q_sort(Item arr[], int left, int right)
{
	int pivot;
	int i = left;
	int j = right - 1;

	// printf("%d %d\n", left, right);
	if (right - left + 1 <= CUTOFF)
	{
		insertion(arr, right - left + 1);
	}
	else
	{
		pivot = median_of_three(arr, left, right);
		while(1)
		{
			while(arr[++i] < pivot);
			while(arr[--j] > pivot);
			if (i < j)
				swap(arr, i, j);	
			else 
				break;		
		}
		swap(arr, i, right - 1);
		q_sort(arr, left, i - 1);
		q_sort(arr, i + 1, right);	
	}
	
}







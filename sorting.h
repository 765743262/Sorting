#ifndef SORTING_H_
#define SORTING_H_

typedef int Item;
enum alg_type 
{
	INSERTION,
	SHELL,
	HEAP,
	MERGE,
	QUICK,
	BUCKET

};
void Sort(Item arr[], int size, enum alg_type alg);
#endif
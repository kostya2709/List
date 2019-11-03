#include <stdlib.h>

const int list_start_size = 10;

struct List
{
    double* data;
	int* next;
	int* prev;
	int size;
	int max_size;
	int head;
	int tail;

};

int List_Construct (List* list1);

#include <stdlib.h>
#include <stdio.h>

#define DUMP( list1 ) List_Dump ( &list1, #list1 );

const int list_start_size = 5;

const int POISON = -666;

struct List
{
    double* data;
	int* next;
	int* prev;
	int size;
	int max_size;
	int head;
	int tail;
	int free;

};

/*! This function creates a list!
@param[in] Pointer to the list.
\return Returns 0 if the function behaves correctly.
*/
int List_Construct (List* list1);


int List_Dump (List* list1, char* list_name);

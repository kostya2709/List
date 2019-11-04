#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DUMP( list1 ); List_Dump ( &list1, #list1 );

const int list_start_size = 7;

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


/*! This function prints the main information of the list.
Attention! This function is to be required only from #define DUMP(); .
@param[in] Pointer to the list.
@param[in] Name of the list.
\return Returns 0 if the function behaves correctly.
*/
int List_Dump (List* list1, char* list_name);


/*! This function inserts a member of the list after an elements of it.
@param[in] Pointer to the list.
@param[in] Number of the list after which another is to be inserted.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_After (List* list1, int location, double elem);


/*! This function inserts a member of the list before an elements of it.
@param[in] Pointer to the list.
@param[in] Number of the list before which another is to be inserted.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_Before (List* list1, int location, double elem);


/*!This function checks whether location is valid.
@param[in] Pointer to the list.
@param[in] Number of the list to check.
*/
int Error_Check (List* list1, int location);

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DUMP( list1 ); List_Dump ( &list1, #list1 );

const int list_start_size = 5;

const int FILE_NAME_SIZE = 20;

typedef double elem_t;
#define PRINTF_ELEM_T "%g"

const int POISON = -666;

const int EMPTY = -27;

struct List
{
    elem_t* data;
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
int List_Dump (const List* list1, char* list_name);


/*! This function inserts a member of the list after an elements of it.
@param[in] Pointer to the list.
@param[in] Number of the list after which another is to be inserted.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_After (List* list1, int location, elem_t elem);


/*! This function inserts a member of the list before an elements of it.
@param[in] Pointer to the list.
@param[in] Number of the list before which another is to be inserted.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_Before (List* list1, int location, elem_t elem);


/*! This function inserts a member of the list to the first element.
@param[in] Pointer to the list.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_Front (List* list1, elem_t elem);


/*! This function inserts a member of the list to the last element.
@param[in] Pointer to the list.
@param[in] The element to insert.
\return Returns 0 if the function behaves correctly.
*/
int Insert_Back (List* list1, elem_t elem);

/*!This function checks whether location is valid.
@param[in] Pointer to the list.
@param[in] Number of the list to check.
@param[in] min Minimal available number.
@param[in] max Maximal available number.
@param[in] dead Unavailable list element.
*/
int Error_Check (const List* list1, int location, int min);


/*! This function deletes a member of the list.
@param[in] Pointer to the list.
@param[in] Number of the list to delete.
\return Returns 0 if the function behaves correctly.
*/
int Delete (List* list1, int location);

/*! This function changes the allocated memory.
@param[in] Pointer to the list.
@param [in] New size of list.
\return Returns 0 if the function behaves correctly.
*/
int List_Realloc (List* list1, int new_size);

/*! This function cleans memory used by the list during the work with it.
Attention! Use only after the work with the list.
@param[in] Pointer to the list.
\return Returns 0 if the function behaves correctly.
*/
int List_Destruct (List* list1);

/*!This function converts the main information about the list to graph.
@param[in] Pointer to the list.
\return Returns 0 if the function behaves correctly.
*/
int List_Dump_Graph (const List* list1);

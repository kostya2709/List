#include "List_Header.h"


int List_Construct (List* list1)
{
    list1->data = (double*)calloc (1, list_start_size * sizeof (double));
    *list1->data = POISON;
    list1->next = (int*)calloc (1, list_start_size * sizeof (int));
    list1->prev = (int*)calloc (1, list_start_size * sizeof (int));

    list1->size = list_start_size;
    list1->max_size = list_start_size;
    list1->head = 1;
    list1->tail = 1;
    list1->free = 1;

    int i = 0;
    *list1->prev = 0;
    *(list1->prev + 1) = 0;
    for (i = 2; i < list1->size; i++)
        *(list1->prev + i) = POISON;

    *list1->next = 0;

    for (i = 1; i < list1->size; i++)
        *(list1->next + i) = i + 1;



    return 0;
}


int List_Dump (List* list1, char* list_name)
{
    printf ("\n\n\tList_name: %s\n", list_name);
    printf ("\tList max_size: %d\n", list1->max_size);
    printf ("\tList size: %d\n", list1->size);
    printf ("\tList elements:\n");

    int i = 0;
    for (i = 0; i < list1->size; i++)
        printf ("\t\tdata [%d] = %.lf\n", i, *(list1->data + i));

    printf ("\n\tArray of next elements:\n");
    for (i = 0; i < list1->size; i++)
        printf ("\t\tnext [%d] = %d\n", i, *(list1->prev + i));

    printf ("\n\tArray of previous elements:\n");
    for (i = 0; i < list1->size; i++)
        printf ("\t\tprev [%d] = %d\n", i, *(list1->next + i));

    printf ("\n\nList head: %d\n", list1->head);
    printf ("List tail: %d\n", list1->tail);
    printf ("List free: %d\n\n\n", list1->free);

}

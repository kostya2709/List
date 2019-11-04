#include "List_Header.h"


int List_Construct (List* list1)
{
    list1->data = (double*)calloc (1, list_start_size * sizeof (double));
    *list1->data = POISON;
    list1->next = (int*)calloc (1, list_start_size * sizeof (int));
    list1->prev = (int*)calloc (1, list_start_size * sizeof (int));

    list1->size = 0;
    list1->max_size = list_start_size;
    list1->head = 0;
    list1->tail = 0;
    list1->free = 1;

    int i = 0;
    *list1->prev = 0;
    *(list1->prev + 1) = 0;
    for (i = 2; i < list1->max_size; i++)
        *(list1->prev + i) = POISON;

    *list1->next = 0;
    *(list1->next + list1->max_size) = 0;

    for (i = 1; i < list1->max_size - 1; i++)
        *(list1->next + i) = i + 1;



    return 0;
}

int Insert_After (List* list1, int location, double elem)
{

    assert (list1);

    if (Error_Check (list1, location))
        return -1;

    list1->size += 1;
    int pos = list1->free;
    list1->free = *(list1->next + pos);

    *(list1->data + pos) = elem;


    if (location == 0)
    {
        int ex_first = list1->head;
        list1->head = pos;

        *(list1->next + pos) = ex_first;
        *(list1->prev + pos) = 0;

        if (ex_first)
            *(list1->prev + ex_first) = pos;

        if (list1->tail == 0)
            list1->tail = pos;

    }

    else
    {
        if (location == list1->tail)
            list1->tail = pos;

        int next_el = *(list1->next + location);
        *(list1->next + location) = pos;

        *(list1->prev + pos) = location;
        *(list1->next + pos) = next_el;
        if (next_el)
            *(list1->prev + next_el) = pos;
    }



    return 0;

}


int Insert_Before (List* list1, int location, double elem)
{

    assert (list1);

    if (Error_Check (list1, location))
        return -1;
    if (location == 0)
        return -1;

    list1->size += 1;
    int pos = list1->free;
    list1->free = *(list1->next + pos);

    *(list1->data + pos) = elem;


        int prev_el = *(list1->prev + location);
        if (prev_el)
            *(list1->next + prev_el) = pos;

        *(list1->prev + location) = pos;
        *(list1->next + pos) = location;
        *(list1->prev + pos) = prev_el;

        if (!prev_el)
            list1->head = pos;


    return 0;

}
int List_Dump (List* list1, char* list_name)
{
    printf ("\n\n\tList_name: %s\n", list_name);
    printf ("\tList max_size: %d\n", list1->max_size);
    printf ("\tList size: %d\n", list1->size);
    printf ("\tList elements:\n");

    int i = 0;
    for (i = 0; i < list1->max_size; i++)
        printf ("\t\tdata [%d] = %.lf\n", i, *(list1->data + i));

    printf ("\n\tArray of next elements:\n");
    for (i = 0; i < list1->max_size; i++)
        printf ("\t\tnext [%d] = %d\n", i, *(list1->next + i));

    printf ("\n\tArray of previous elements:\n");
    for (i = 0; i < list1->max_size; i++)
        printf ("\t\tprev [%d] = %d\n", i, *(list1->prev + i));

    printf ("\n\nList head: %d\n", list1->head);
    printf ("List tail: %d\n", list1->tail);
    printf ("List free: %d\n\n\n", list1->free);

    return 0;
}

int Error_Check (List* list1, int location)
{
    if (location < 0)
    {
        printf ("Error! Invalid index of list for Insert_After!\n");
        printf ("Expected a number above zero\n");
        printf ("Received: %d\n", location);

        return -1;
    }

    if (*(list1->prev + location) == POISON || location > list1->max_size)
    {
        printf ("Error! Invalid index of list for Insert_After!\n");
        printf ("Expected an existing element from zero to max_size! (max_size = %d)\n", list1->max_size);
        printf ("Received: %d\n", location);

        return -1;
    }

    return 0;
}

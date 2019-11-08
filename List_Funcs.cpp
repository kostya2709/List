#include "List_Header.h"


int List_Construct (List* list1)
{
    list1->data = (double*)calloc (1, list_start_size * sizeof (elem_t));
    *list1->data = POISON;

    list1->next = (int*)calloc (1, list_start_size * sizeof (int));
    list1->prev = (int*)calloc (1, list_start_size * sizeof (int));

    if (!list1->data || !list1->next || !list1->prev)
    {
        printf ("Error of allocation!\n");
        return -1;
    }

    list1->size = 0;
    list1->max_size = list_start_size;
    list1->head = 0;
    list1->tail = 0;
    list1->free = 1;

    int i = 0;
    for (i = 2; i < list1->max_size; i++)
        *(list1->prev + i) = POISON;

    for (i = 1; i < list1->max_size; i++)
        *(list1->next + i) = i + 1;

    for (i = 1; i < list1->max_size; i++)
        *(list1->data + i) = EMPTY;

    return 0;
}

int Insert_After (List* list1, int location, elem_t elem)
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

    if (list1->size + 1 == list1->max_size)
    {
        List_Realloc(list1, list1->max_size * 2);
        list1->max_size *= 2;
    }

    return 0;

}


int Insert_Before (List* list1, int location, elem_t elem)
{

    assert (list1);

    if (Error_Check (list1, location))
        return -1;
    if (location == 0)
    {
        printf ("Error! You cannot insert before zero!\n");
        return -1;
    }

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

    if (list1->size + 1 == list1->max_size)
    {
        List_Realloc(list1, list1->max_size * 2);
        list1->max_size *= 2;
    }


    return 0;

}

int Insert_Front (List* list1, elem_t elem)
{
    Insert_Before (list1, list1->head, elem);
}


int Insert_Back (List* list1, elem_t elem)
{
    Insert_After (list1, list1->tail, elem);
}


int Delete (List* list1, int location)
{

    assert (list1);

    if (Error_Check (list1, location))
        return -1;
    if (location == 0)
    {
        printf ("Error! You cannot delete zero!\n");
        return -1;
    }

    list1->size -= 1;

    if (location == list1->head)
    {
        int next_el = *(list1->next + location);
        list1->head = next_el;
        *(list1->prev + next_el) = 0;
    }

    if (location == list1->tail)
    {
        int prev_el = *(list1->prev + location);
        list1->tail = prev_el;
        *(list1->next + prev_el) = 0;
    }

    else
    {
        int next_el = *(list1->next + location);
        int prev_el = *(list1->prev + location);

        *(list1->prev + next_el) = prev_el;
        *(list1->next + prev_el) = next_el;
    }

    *(list1->data + location) = 0;

    *(list1->next + location) = list1->free;
    *(list1->prev + location) = POISON;
    list1->free = location;


    return 0;

}

int Delete_After (List* list1, int location)
{

    assert (list1);

    if (Error_Check (list1, location))
        return -1;
    if (location == 0)
    {
        printf ("Error! You cannot delete a number after 0!\n");
        return -1;
    }
    if (location == list1->tail)
    {
        printf ("Error! You cannot delete a number after the list tail!\n");
        return -1;
    }

    list1->size -= 1;

        int next_el = *(list1->next + location);

        if (next_el == list1->tail)
        {
            *(list1->next + location) = 0;
            list1->tail = location;
        }

        else
        {
            int next_next_el = *(list1->next + next_el);
            *(list1->prev + next_next_el) = location;
            *(list1->next + location) = next_next_el;
        }


    *(list1->data + next_el) = 0;

    *(list1->next + next_el) = list1->free;
    *(list1->prev + next_el) = POISON;
    list1->free = next_el;

    return 0;

}


int List_Dump (const List* list1, char* list_name)
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

int Error_Check (const List* list1, int location)
{
    if (location < 0)
    {
        printf ("Error! Invalid index of list!\n");
        printf ("Expected a number above zero\n");
        printf ("Received: %d\n", location);

        return -1;
    }

    if (*(list1->prev + location) == POISON || location > list1->max_size)
    {
        printf ("Error! Invalid index of list!\n");
        printf ("Expected an existing element from zero to max_size! (max_size = %d)\n", list1->max_size);
        printf ("Received: %d\n", location);

        return -1;
    }

    return 0;
}

int List_Realloc (List* list1, int new_size)
{
    assert (list1);

    int prev_size = list1->max_size;

    list1->data = (elem_t*)realloc (list1->data, new_size * sizeof (elem_t));
    list1->next = (int*)realloc (list1->next, new_size * sizeof (int));
    list1->prev = (int*)realloc (list1->prev, new_size * sizeof (int));

    if (!list1->data || !list1->next || !list1->prev)
    {
        printf ("Error of reallocation!\n");
        return -1;
    }

    if (prev_size < new_size)
    {
        int i = 0;

        for (i = prev_size; i < new_size; i++)
            *(list1->data + i) = EMPTY;

        for (i = prev_size; i < new_size; i++)
            *(list1->prev + i) = POISON;

        for (i = prev_size; i < new_size; i++)
            *(list1->next + i) = i + 1;
    }

    return 0;
}

int List_Destruct (List* list1)
{
    assert (list1);

    if (!list1->data || !list1->next || !list1->prev)
        return -1;

    free (list1->data);
    free (list1->next);
    free (list1->prev);

    return 0;
}

int List_Dump_Graph (const List* list1)
{
    FILE* f = fopen ("graph_dump.gv", "w");

    fprintf (f, "digraph First{\n");
    fprintf (f, "node [shape=\"record\", style=\"filled\", fillcolor=\"green\"];\n");
    fprintf (f, "rankdir=\"LR\";\n");
    fprintf (f, "dpi=\"300\";\n");

    fprintf (f, "\"head\" [label = \"head\"];\n");
    fprintf (f, "\"tail\" [label = \"tail\"];\n");

    fprintf (f, "node [fillcolor=\"lightblue\"];");

    int number = list1->head;
    int i = 0;
    while (true)
    {
        fprintf (f, "\"box%d\"  [label = \"adress = %d|value = " PRINTF_ELEM_T "|next = %d|prev = %d\"];\n\n",
                 i, number, *(list1->data + number), *(list1->next + number), *(list1->prev + number));
        i++;
        if (number == list1->tail)
            break;
        number = *(list1->next + number);
    }

    fprintf (f, "\"head\"->\"box0\";\n");

    int j = 0;
    for (j = 0; j < i - 1; j++)
        fprintf (f, "\"box%d\" -> \"box%d\";\n", j, j + 1);

    fprintf (f, "\"box%d\" -> \"tail\";\n\n", j, 0);

    fprintf (f, "node [fillcolor=\"green\"];");

    fprintf (f, "\"info\" [label = \"Info|head = %d|tail = %d|free = %d|size = %d|max_size = %d\"]\n", list1->head, list1->tail, list1->free, list1->size, list1->max_size);


    fprintf (f, "}");

    fclose (f);

    system ("dot -Tpng graph_dump.gv -o list.png");

    return 0;
}

int List_Sorting (List* list1, int left, int right)
{

    List_Qsort (1, 2, list1);
}

int List_Qsort (int left, int right, List* list1)
{
/*
        if (left >= right)
            return 0;

        int mid = (left + right) / 2;
        Swap ((char*)arr + left * ssize, (char*)arr + mid * ssize, ssize);

        int last = left;
        int i = 0;

        for (i = left; i <= right; i++)
            if (compare ((void*)((char*)arr + left * ssize), (void*)((char*)arr + i * ssize)) > 0)
                Swap ((char*)arr + i * ssize, (char*)arr + (++last) * ssize, ssize);

        Swap ((char*)arr + left * ssize, (char*)arr + last * ssize, ssize);

        Qsort (left, last -  1, arr, ssize, compare);
        Qsort (last + 1, right, arr, ssize, compare);

*/
}

void Swap (void* a, void* b, int sizze)
    {
        int i;
        size_t temp;
        for (i = 0; i < sizze; i++)
        {
            temp = (size_t)(*((char*)a + i));
            *((char*)a + i) = *((char*)b + i);
            *((char*)b + i) = temp;
        }
    }

void List_Swap (List* list1, int n1, int n2)
{/*
    Swap (list1->data + n1, list1->data + n2, sizeof (elem_t));

    Swap (list1->next + n1, list1->next + n2, sizeof (*list1->next));

    Swap (list1->prev + n1, list1->prev + n2, sizeof (*list1->prev));

#define Change_Prop(prop, elem1, elem2);         \
#define LIST list1->                            \
if (LIST##prop == elem1)                       \
    list1->free = elem2;                         \
else if (list1->free == elem2)                  \
    list1->free = elem1;

    Change_Prop (free, n1, n2);
    Change_Prop (head, n1, n2);
    Change_Prop (tail, n1, n2);

#undef Change_Prop
*/
    return;

}

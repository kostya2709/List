//!@file

#include "List_Header.h"

int main()
{
    List list1 = {};

    List_Construct(&list1);

    DUMP (list1);

    Insert_After(&list1, 0, 27);

    DUMP (list1);

    Insert_After(&list1, 1, 28);

    DUMP (list1);

    Insert_After(&list1, 2, 29);

    DUMP (list1);

    Insert_After(&list1, 3, 30);

    DUMP (list1);

    Delete (&list1, 3);

    DUMP (list1);

    Insert_After(&list1, 4, 70);

    DUMP (list1);

    Insert_Front (&list1, 228);

    DUMP (list1);

    Insert_Back (&list1, 111);

    DUMP (list1);

    List_Dump_Graph (&list1);

    if (List_Destruct (&list1))
        printf ("Error in pointers of the list in List_Destruct!\n");


    return 0;
}

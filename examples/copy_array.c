#include "array.h"

int main()
{
    printf("===== Array Int =====\n");
    struct int_array *array_int = create_int_array(7);
    display_int_array(array_int);

    printf("\n");

    printf("===== Copy Matrix Int =====\n");
    struct int_array *array_copy = copy_int_array(array_int);
    display_int_array(array_copy);

    printf("\n");

    free_int_array(&array_int);
    free_int_array(&array_copy);

    return 0;
}
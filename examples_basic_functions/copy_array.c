#include "array.h"

int main()
{
    printf("===== Array Int =====\n");
    struct int_array *array_int = create_int_array(7);
    display_int_array(array_int);

    printf("\n");

    printf("===== Copy Matrix Int =====\n");
    struct int_array *array_int_copy = copy_int_array(array_int);
    display_int_array(array_int_copy);

    printf("\n");

    free_int_array(&array_int);
    free_int_array(&array_int_copy);

    printf("\n\n\n");

    printf("===== Array Int =====\n");
    struct float_array *array_float = create_float_array(7);
    display_float_array(array_float);

    printf("\n");

    printf("===== Copy Matrix Int =====\n");
    struct float_array *array_float_copy = copy_float_array(array_float);
    display_float_array(array_float_copy);

    printf("\n");

    free_float_array(&array_float);
    free_float_array(&array_float_copy);

    return 0;
}
#include "array.h"

int main()
{
    printf("===== Matrix Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);

    printf("\n");

    printf("===== Initialized Matrix Int =====\n");
    initialization_int_array(array_int, 5);
    display_int_array(array_int);
    free_int_array(&array_int);

    printf("\n");

    printf("===== Error Matrix Int =====\n");
    struct int_array *array_int_error = create_int_array(-5);
    display_int_array(array_int_error);

    printf("\n");

    printf("===== Error Initialized Matrix Int =====\n");
    initialization_int_array(array_int_error, 5);
    display_int_array(array_int_error);
    free_int_array(&array_int_error);

    return 0;
}
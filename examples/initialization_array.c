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

    return 0;
}
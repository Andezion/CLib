#include "array.h"

int main(void)
{
    printf("===== Array Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);
    destroy_int_array(&array_int);

    printf("\n");

    printf("===== Error Array Int =====\n");
    struct int_array *error_numbers_array_int = create_int_array(-1);
    display_int_array(error_numbers_array_int);
    destroy_int_array(&error_numbers_array_int);

    printf("\n\n\n");

    printf("===== Array Float =====\n");
    struct float_array *array_float = create_float_array(5);
    display_float_array(array_float);
    destroy_float_array(&array_float);

    printf("\n");

    printf("===== Error Array Float =====\n");
    struct float_array *error_numbers_array_float = create_float_array(-1);
    display_float_array(error_numbers_array_float);
    destroy_float_array(&error_numbers_array_float);

    return 0;
}
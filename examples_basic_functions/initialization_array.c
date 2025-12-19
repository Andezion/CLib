#include "array.h"

int main()
{
    printf("===== Array Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);

    printf("\n");

    printf("===== Initialized Array Int =====\n");
    initialization_int_array(array_int, 5);
    display_int_array(array_int);
    free_int_array(&array_int);

    printf("\n");

    printf("===== Error Array Int =====\n");
    struct int_array *array_int_error = create_int_array(-5);
    display_int_array(array_int_error);

    printf("\n");

    printf("===== Error Initialized Array Int =====\n");
    initialization_int_array(array_int_error, 5);
    display_int_array(array_int_error);
    free_int_array(&array_int_error);

    printf("\n\n\n");

    printf("===== Array Float =====\n");
    struct float_array *array_float = create_float_array(5);
    display_float_array(array_float);

    printf("\n");

    printf("===== Initialized Array Float =====\n");
    initialization_float_array(array_float, 4.7);
    display_float_array(array_float);
    free_float_array(&array_float);

    printf("\n");

    printf("===== Error Array Float =====\n");
    struct float_array *error_numbers_array_float = create_float_array(-1);
    display_float_array(error_numbers_array_float);
    free_float_array(&error_numbers_array_float);

    printf("\n");

    printf("===== Initialized Error Array Float =====\n");
    initialization_float_array(error_numbers_array_float, 4.7);
    display_float_array(error_numbers_array_float);
    free_float_array(&error_numbers_array_float);

    return 0;
}
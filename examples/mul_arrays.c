#include "array.h"
#include "array_math.h"

int main()
{
    srand(time(NULL));

    printf("===== Array Int One =====\n");
    struct int_array *array_int_one = create_int_array(5);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Random Initialized Array Int One =====\n");
    initialization_random_int_array(array_int_one, 0, 9);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Array Int Two =====\n");
    struct int_array *array_int_two = create_int_array(5);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Random Initialized Array Int Two =====\n");
    initialization_random_int_array(array_int_two, 0, 9);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Result Matrix Int =====\n");

    struct int_array *array_result_int = mul_int_arrays(2, 5, array_int_one, array_int_two);
    display_int_array(array_result_int);

    free_int_array(&array_result_int);
    free_int_array(&array_int_one);
    free_int_array(&array_int_two);

    printf("\n\n\n");

    printf("===== Matrix Float One =====\n");
    struct float_array *array_float_one = create_float_array(3);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Random Initialized Matrix Float One =====\n");
    initialization_random_float_array(array_float_one, 0.0, 9.0);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Matrix Float Two =====\n");
    struct float_array *array_float_two = create_float_array(3);
    display_float_array(array_float_two);

    printf("\n");

    printf("===== Random Initialized Matrix Float Two =====\n");
    initialization_random_float_array(array_float_two, 0.0, 9.0);
    display_float_array(array_float_two);

    printf("\n");

    printf("===== Result Matrix Float =====\n");

    struct float_array *array_result_float = mul_float_arrays(2, 3, array_float_one, array_float_two);
    display_float_array(array_result_float);

    free_float_array(&array_result_float);
    free_float_array(&array_float_one);
    free_float_array(&array_float_two);

    return 0;
}
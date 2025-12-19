#include "array_math.h"
#include "array.h"

int main()
{
    srand(time(NULL));
    const int64_t value_to_add_int = 5;

    printf("===== Array Float One =====\n");
    struct int_array *array_int_one = create_int_array(5);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Random Initialized Array Float One =====\n");
    initialization_random_int_array(array_int_one, 0, 9);
    display_int_array(array_int_one);

    printf("\n");

    printf("===== Sub Value from Array Float =====\n");
    struct int_array *result_int_matrix = sub_value_from_int_arrays(1, 5, value_to_add_int, array_int_one);
    display_int_array(result_int_matrix);

    printf("\n");

    printf("===== Array Float Two =====\n");
    struct int_array *array_int_two = create_int_array(5);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Random Initialized Array Float Two =====\n");
    initialization_random_int_array(array_int_two, 0, 9);
    display_int_array(array_int_two);

    printf("\n");

    printf("===== Sub Value from Arrays Float =====\n");
    struct int_array *result_int_matrices = sub_value_from_int_arrays(2, 5, value_to_add_int, array_int_one, array_int_two);
    display_int_array(result_int_matrices);

    printf("\n");

    free_int_array(&array_int_one);
    free_int_array(&array_int_two);
    free_int_array(&result_int_matrix);
    free_int_array(&result_int_matrices);

    printf("\n\n\n");

    const float64_t value_to_add_float = 5.0;

    printf("===== Array Float One =====\n");
    struct float_array *array_float_one = create_float_array(5);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Random Initialized Array Float One =====\n");
    initialization_random_float_array(array_float_one, 0, 9);
    display_float_array(array_float_one);

    printf("\n");

    printf("===== Sub Value from Array Float =====\n");
    struct float_array *result_float_array = sub_value_from_float_arrays(1, 5, value_to_add_float, array_float_one);
    display_float_array(result_float_array);

    printf("\n");

    printf("===== Matrix Float Two =====\n");
    struct float_array *array_float_two = create_float_array(5);
    display_float_array(array_float_two);

    printf("\n");

    printf("===== Random Initialized Matrix Float Two =====\n");
    initialization_random_float_array(array_float_two, 0, 9);
    display_float_array(array_float_two);

    printf("\n");

    printf("===== Sub Value from Matrices Float =====\n");
    struct float_array *result_float_arrays = sub_value_from_float_arrays(2, 5, value_to_add_float, array_float_one, array_float_two);
    display_float_array(result_float_arrays);

    free_float_array(&array_float_one);
    free_float_array(&array_float_two);
    free_float_array(&result_float_array);
    free_float_array(&result_float_arrays);

    return 0;
}
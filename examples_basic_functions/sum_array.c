#include "array.h"
#include "array_math.h"

int main()
{
    printf("===== Matrix Int =====\n");
    struct int_array *array_int = create_int_array(5);
    display_int_array(array_int);

    printf("\n");

    printf("===== Sum Matrix Int =====\n");
    int64_t sum_array_int = sum_int_array(array_int);
    printf("Sum is = %lld\n", sum_array_int);

    printf("\n\n\n");

    printf("===== Initialized Array Int =====\n");
    initialization_int_array(array_int, 5);
    display_int_array(array_int);

    printf("\n");

    printf("===== Sum Array Int =====\n");
    sum_array_int = sum_int_array(array_int);
    printf("Sum is = %lld\n", sum_array_int);
    free_int_array(&array_int);

    printf("\n\n\n");

    printf("===== Array Float =====\n");
    struct float_array *array_float = create_float_array(5);
    display_float_array(array_float);

    printf("\n");

    printf("===== Sum Array Float =====\n");
    float64_t sum_float = sum_float_array(array_float);
    printf("Sum is = %f\n", sum_float);

    printf("\n\n\n");

    printf("===== Initialized Matrix Float =====\n");
    initialization_float_array(array_float, 6.2);
    display_float_array(array_float);

    printf("\n");

    printf("===== Sum Matrix Float =====\n");
    sum_float = sum_float_array(array_float);
    printf("Sum is = %f\n", sum_float);
    free_float_array(&array_float);

    return 0;
}

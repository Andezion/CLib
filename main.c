#include <stdio.h>
#include "array_2d.h"

int main(void)
{
    int64_t **array = NULL;
    create_array_i_2d_init_rect(&array, 5, 6, 8);

    display_array_i_2d(array,5, 6);

    return 0;
}

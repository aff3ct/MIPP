#include <mipp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    rvd_float64_t r1 = mipp_set1_float64(1.0);
    rvd_float64_t r2 = mipp_set1_float64(2.0);
    rvd_float64_t r3 = mipp_add_float64(r1, r2);
    printf("result: %f\n", mipp_get_float64(r3, 0));
    return 0;
}
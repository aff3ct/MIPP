// gcc dumb.c -I../include -Wall -mavx2 -o dumb.bin

#include <mipp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	rvd_float32_t r1 = mipp_set1_float32(1.0);
	rvd_float32_t r2 = mipp_set1_float32(2.0);
	rvd_float32_t r3 = mipp_add_float32(r1, r2);
	printf("result: %f\n", mipp_get_float32(r3, 0));
	return 0;
}

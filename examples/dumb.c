// gcc dumb.c -I../include -Wall -mavx2 -o dumb.bin

#include <mipp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_v(float32_t* v, char* name)
{
	int i;
	printf("%s = [", name);
	for (i = 0; i < MIPP_N_FLOAT32; i++)
		printf("%f,", v[i]);
	printf("]\n");
}

int main()
{
#if defined(MIPP_PRINT_INFO)
	mipp_info();
	printf("\n");
#endif

	srand(time(NULL));

	float32_t a1[MIPP_N_FLOAT32], a2[MIPP_N_FLOAT32];
	for (size_t i = 0; i < MIPP_N_FLOAT32; i++) {
		a1[i] = (float32_t)rand() / (float32_t)RAND_MAX;
		a2[i] = (float32_t)rand() / (float32_t)RAND_MAX;
	}

	vd_float32_t vd1 = mipp_loadu_float32(a1); // stack arrays: no alignment guarantee
	vd_float32_t vd2 = mipp_loadu_float32(a2);
	vd_float32_t vd3 = mipp_add_float32(vd1, vd2);

	// printf("result: %f\n", mipp_get_float32(vd3, 0));
	float32_t a3[MIPP_N_FLOAT32];
	mipp_storeu_float32(a3, vd3);
	print_v(a3, "result");

	return 0;
}

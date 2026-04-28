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

	rvd_float32_t r1 = mipp_load_float32(a1);
	rvd_float32_t r2 = mipp_load_float32(a2);
	rvd_float32_t r3 = mipp_add_float32(r1, r2);

	// printf("result: %f\n", mipp_get_float32(r3, 0));
	float32_t a3[MIPP_N_FLOAT32];
	mipp_storeu_float32(a3, r3);
	print_v(a3, "result");

	return 0;
}

// gcc mipp.c -I../include -Wall -mavx2 -o mipp_c.bin

#include <stdio.h>

#include <mipp.h>

void print_v(float32_t* v, char* name)
{
	int i;
	printf("%s = [", name);
	for (i = 0; i < MIPP_N_FLOAT32 * 4; i++)
		printf("%f,", v[i]);
	printf("]\n");
}

int main(int argc, char** argv)
{
	mipp_info();
	printf("\n");

	int i;
	float32_t a1[MIPP_N_FLOAT32 * 4];
	float32_t a2[MIPP_N_FLOAT32 * 4];
	float32_t a3[MIPP_N_FLOAT32 * 4];

	rvd_float32_m4_t rvd1;
	rvd_float32_m4_t rvd2;
	rvd_float32_m4_t rvd3;

	for (i = 0; i < MIPP_N_FLOAT32 * 4; i++) {
		a1[i] = i+0;
		a2[i] = i+1;
	}

	print_v(a1, "a1");
	print_v(a2, "a2");

	rvd1 = mipp_loadu_float32_m4(a1);
	rvd2 = mipp_loadu_float32_m4(a2);

	rvd3 = mipp_add_float32_m4(rvd1, rvd2);

	mipp_storeu_float32_m4(a3, rvd3);

	print_v(a3, "a3");

	return 0;
}

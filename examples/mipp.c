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
#if defined(MIPP_PRINT_INFO)
	mipp_info();
	printf("\n");
#endif

	int i;
	float32_t a1[MIPP_N_FLOAT32 * 4];
	float32_t a2[MIPP_N_FLOAT32 * 4];
	float32_t a3[MIPP_N_FLOAT32 * 4];

	vd_float32_m4_t vd1;
	vd_float32_m4_t vd2;
	vd_float32_m4_t vd3;

	for (i = 0; i < MIPP_N_FLOAT32 * 4; i++) {
		a1[i] = i+0;
		a2[i] = i+1;
	}

	print_v(a1, "a1");
	print_v(a2, "a2");

	vd1 = mipp_loadu_float32_m4(a1);
	vd2 = mipp_loadu_float32_m4(a2);

	vd3 = mipp_add_float32_m4(vd1, vd2);

	mipp_storeu_float32_m4(a3, vd3);

	print_v(a3, "a3");

	return 0;
}

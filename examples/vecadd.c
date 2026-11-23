// gcc vecadd.c -I../include -Wall -mavx2 -o vecadd.bin

#include <mipp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_SIZE MIPP_N_FLOAT32 * 1000

void vecadd(const float32_t* a1, const float32_t* a2, float32_t* a3)
{
	for (size_t i = 0; i < BUFF_SIZE; i += MIPP_N_FLOAT32)
	{
		vd_float32_t vd1 = mipp_loadu_float32(a1 + i);
		vd_float32_t vd2 = mipp_loadu_float32(a2 + i);
		vd_float32_t vd3 = mipp_add_float32(vd1, vd2);
		mipp_storeu_float32(a3 + i, vd3);
	}
}

void vecadd_mask(const float32_t* a1, const float32_t* a2, float32_t* a3)
{
	for (size_t i = 0; i < BUFF_SIZE; i += MIPP_N_FLOAT32)
	{
		vd_float32_t vd1 = mipp_loadu_float32(a1 + i);
		vd_float32_t vd2 = mipp_loadu_float32(a2 + i);
		vm_float32_t vm1 = mipp_cmplt_float32(vd1, vd2);
		vd_float32_t vd3 = mipp_add_float32_mask(vm1, vd1, vd2);
		mipp_storeu_float32(a3 + i, vd3);
	}
}

float32_t vecadd_mask_red(const float32_t* a1, const float32_t* a2)
{
	vd_float32_t sum = mipp_set0_float32();
	for (size_t i = 0; i < BUFF_SIZE; i += MIPP_N_FLOAT32)
	{
		vd_float32_t vd1 = mipp_loadu_float32(a1 + i);
		vd_float32_t vd2 = mipp_loadu_float32(a2 + i);
		vm_float32_t vm1 = mipp_cmplt_float32(vd1, vd2);
		vd_float32_t vd3 = mipp_add_float32_maskz(vm1, vd1, vd2);

		sum = mipp_add_float32(mipp_hadd_float32(vd3), sum);
	}
	return mipp_get_float32(sum, 0);
}

float32_t vecadd_mask_red2(const float32_t* a1, const float32_t* a2)
{
	float32_t sum = 0.f;
	for (size_t i = 0; i < BUFF_SIZE; i += MIPP_N_FLOAT32)
	{
		vd_float32_t vd1 = mipp_loadu_float32(a1 + i);
		vd_float32_t vd2 = mipp_loadu_float32(a2 + i);
		vm_float32_t vm1 = mipp_cmplt_float32(vd1, vd2);
		vd_float32_t vd3 = mipp_add_float32_maskz(vm1, vd1, vd2);

		sum += mipp_hadd_to_scal_float32(vd3);
	}
	return sum;
}

int main()
{
#if defined(MIPP_PRINT_INFO)
	mipp_info();
	printf("\n");
#endif

	srand(time(NULL));

	float32_t a1[BUFF_SIZE], a2[BUFF_SIZE];
	for (size_t i = 0; i < BUFF_SIZE; i++)
	{
		a1[i] = (float32_t)rand() / (float32_t)RAND_MAX;
		a2[i] = (float32_t)rand() / (float32_t)RAND_MAX;
	}

	// float32_t a3[BUFF_SIZE];
	// vecadd_mask(a1, a2, a3);
	// float32_t sum = 0.f;
	// for (size_t i = 0; i < BUFF_SIZE; i++)
	// 	sum += a3[i];
	// printf("sum: %f\n", sum);

	float32_t sum = vecadd_mask_red2(a1, a2);
	printf("sum: %f\n", sum);

	return 0;
}

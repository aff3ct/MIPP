#ifndef QUICK_SORTER_HPP
#define QUICK_SORTER_HPP

#include <cmath>
#include <vector>
#include <algorithm>
#include <cassert>

#include <mipp.h>

template <typename T>
class Quick_sorter
{
private:
	const int         size;
	mipp::vector<int> R;
	mipp::vector<T>   K;
public:
	Quick_sorter(const int size) : size(size), R(size +2), K(size + 2)
	{
		std::iota(R.begin() +1 , R.begin() + this->size +1 , 0);

		K[0] = std::numeric_limits<T>::min();
		K[size +1] = std::numeric_limits<T>::max();
	}

	void sort(const T* values, std::vector<int> &pos, const int p_sort = -1)
	{
		const auto M = (p_sort <= 0) ? (int)pos.size() : p_sort;
		std::copy(values, values + size, K.begin() +1);
		std::iota(R.begin(), R.begin() + this->size +2, 0);
		// std::cout << "M: " << M << std::endl;

		// Q1
		auto l = 1;
		auto r = size;
		auto j = r +1;
		do
		{
			auto i = l;
			j = r +1;
			auto KK = K[R[l]];

			while (j > i)
			{
				do
				{
					i++;
				}
				while(K[R[i]] < KK);

				do
				{
					j--;
				}
				while(KK < K[R[j]]);

				if(j > i)
				{
					const auto tmp = R[j];
					R[j] = R[i];
					R[i] = tmp;
				}
				else
				{
					const auto tmp = R[l];
					R[l] = R[j];
					R[j] = tmp;

					if(j < M +1)
						l = j +1;
					else
						r = j -1;
				}
			}
		} while (j != M +1);
		for (auto i = 0; i < M; i++)
			pos[i] = R[i +1] -1;
	}
};

#endif /* QUICK_SORTER_HPP */

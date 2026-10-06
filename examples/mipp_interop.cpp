// Compile with:
// g++ -std=c++11 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Werror -O3 -I../include -o mipp_interop_cpp mipp_interop.cpp

#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>

// Granular includes for C++ Object Layer
#include <mipp/obj/fun/add.hpp>
#include <mipp/obj/fun/sub.hpp>
#include <mipp/obj/fun/mul.hpp>
#include <mipp/obj/fun/cmplt.hpp>
#include <mipp/obj/fun/blend.hpp>
#include <mipp/obj/fun/load.hpp>
#include <mipp/obj/fun/loadu.hpp>
#include <mipp/obj/fun/set.hpp>
#include <mipp/obj/fun/set_k.hpp>
#include <mipp/obj/fun/set0.hpp>
#include <mipp/obj/fun/set0_k.hpp>
#include <mipp/obj/fun/set1.hpp>
#include <mipp/obj/fun/set1_k.hpp>
#include <mipp/obj/fun/storeu.hpp>
#include <mipp/obj/fun/andb.hpp>
#include <mipp/obj/fun/andb_k.hpp>
#include <mipp/obj/fun/orb.hpp>
#include <mipp/obj/fun/orb_k.hpp>
#include <mipp/obj/fun/xorb.hpp>
#include <mipp/obj/fun/xorb_k.hpp>
#include <mipp/obj/fun/notb.hpp>
#include <mipp/obj/fun/notb_k.hpp>
#include <mipp/obj/fun/get.hpp>
#include <mipp/obj/fun/get_k.hpp>

// Granular include for C++ Functional Layer (to test C++ Func / C++ Obj interoperability)
#include <mipp/cpp/fun/abs.hpp>

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
#if defined(MIPP_PRINT_INFO)
	mipp_info();
	std::cout << std::endl;
#endif

	constexpr int N = mipp::N<float, 1>();
	std::cout << "MIPP vector width for float: " << N << std::endl;

	std::vector<float> in1(N, 2.0f);
	std::vector<float> in2(N, 5.0f);
	std::vector<float> out(N, 0.0f);

	// 1. Load using Rvd constructor
	mipp::Rvd<float, 1> a(in1.data());
	mipp::Rvd<float, 1> b(in2.data());

	// 2. Operators on Rvd
	auto c = a + b; // 2.0 + 5.0 = 7.0
	assert(c[0] == 7.0f);
	std::cout << "[PASS] c = a + b => " << c[0] << std::endl;

	// 3. Scalar assignment
	c = 10.0f;
	assert(c[0] == 10.0f);
	std::cout << "[PASS] c = 10.0f => " << c[0] << std::endl;

	// 4. Comparison creating Rvm & Boolean Broadcast
	auto mask = (a < b); // 2.0 < 5.0 => true
	assert(mask[0] == true);
	std::cout << "[PASS] mask = (a < b) created, mask[0] = " << mask[0] << std::endl;

	// 4b. Rvm boolean broadcast constructor & assignment
	mipp::Rvm<float, 1> m_bcast_true(true);
	assert(m_bcast_true[0] == true);
	mipp::Rvm<float, 1> m_bcast_false(false);
	assert(m_bcast_false[0] == false);
	m_bcast_false = true;
	assert(m_bcast_false[0] == true);
	std::cout << "[PASS] Rvm boolean broadcast (true/false) verified" << std::endl;

	// 5. Masked add directly with Rvm and Rvd
	auto d = mipp::add(mask, a, b); // 2.0 + 5.0 = 7.0
	assert(d[0] == 7.0f);
	std::cout << "[PASS] d = mipp::add(mask, a, b) => " << d[0] << std::endl;

	// 6. Blend with mask first: blend(m, a, b)
	auto e = mipp::blend(mask, a, b);
	assert(e[0] == a[0]); // mask is true for a < b, so selects a[0] = 2.0
	std::cout << "[PASS] blend(mask, a, b) => " << e[0] << std::endl;

	// 7. C++ Func interoperability: call mipp::abs (from C++ Func) directly passing Rvd!
	// Rvd implicitly converts to rvd, and rvd converts to Rvd:
	mipp::Rvd<float, 1> neg_val(-4.0f);
	mipp::rvd<float, 1> raw_abs = mipp::abs(neg_val); // Rvd -> rvd
	mipp::Rvd<float, 1> abs_val = raw_abs;             // rvd -> Rvd
	assert(abs_val[0] == 4.0f);
	std::cout << "[PASS] C++ Func mipp::abs(Rvd) interoperability => " << abs_val[0] << std::endl;

	// 8. Storeu with Rvd
	mipp::storeu(out.data(), d);
	assert(out[0] == 7.0f);
	std::cout << "[PASS] storeu(out, d) => " << out[0] << std::endl;

	// 9. Masked storeu with Rvm and Rvd
	mipp::storeu(mask, out.data(), a);
	assert(out[0] == 2.0f);
	std::cout << "[PASS] masked storeu(mask, out, a) => " << out[0] << std::endl;

	// 10. Test _obj initializers and free functions
	// 10a. set0_obj
	auto r_zero = mipp::set0_obj<float>();
	static_assert(std::is_same<decltype(r_zero), mipp::Rvd<float, 1>>::value, "Type mismatch for set0_obj");
	assert(r_zero[0] == 0.0f);
	std::cout << "[PASS] set0_obj<float>() => " << r_zero[0] << std::endl;

	// 10b. set1_obj
	auto r_one = mipp::set1_obj<float>(3.14f);
	static_assert(std::is_same<decltype(r_one), mipp::Rvd<float, 1>>::value, "Type mismatch for set1_obj");
	assert(r_one[0] == 3.14f);
	std::cout << "[PASS] set1_obj<float>(3.14f) => " << r_one[0] << std::endl;

	// 10c. loadu_obj
	auto r_loadu = mipp::loadu_obj<float>(in1.data());
	static_assert(std::is_same<decltype(r_loadu), mipp::Rvd<float, 1>>::value, "Type mismatch for loadu_obj");
	assert(r_loadu[0] == 2.0f);
	std::cout << "[PASS] loadu_obj<float>(in1.data()) => " << r_loadu[0] << std::endl;

	// 10d. loadu_obj with mask
	auto r_loadu_maskz = mipp::loadu_obj(mask, in2.data());
	static_assert(std::is_same<decltype(r_loadu_maskz), mipp::Rvd<float, 1>>::value, "Type mismatch for masked loadu_obj");
	assert(r_loadu_maskz[0] == 5.0f);
	std::cout << "[PASS] loadu_obj(mask, in2.data()) => " << r_loadu_maskz[0] << std::endl;

	// 10e. set0_k_obj & set1_k_obj
	auto m_zero = mipp::set0_k_obj<float>();
	static_assert(std::is_same<decltype(m_zero), mipp::Rvm<float, 1>>::value, "Type mismatch for set0_k_obj");
	assert(m_zero[0] == false);
	std::cout << "[PASS] set0_k_obj<float>() => " << m_zero[0] << std::endl;

	auto m_one = mipp::set1_k_obj<float>(1);
	static_assert(std::is_same<decltype(m_one), mipp::Rvm<float, 1>>::value, "Type mismatch for set1_k_obj");
	assert(m_one[0] == true);
	std::cout << "[PASS] set1_k_obj<float>(1) => " << m_one[0] << std::endl;

	// 10f. set_obj and set_k_obj
	alignas(64) float vals[N];
	alignas(64) int32_t kvals[N];
	for (int i = 0; i < N; ++i) {
		vals[i] = static_cast<float>(i * 10);
		kvals[i] = (i % 2 == 0) ? 1 : 0;
	}
	auto r_set = mipp::set_obj<float>(vals);
	static_assert(std::is_same<decltype(r_set), mipp::Rvd<float, 1>>::value, "Type mismatch for set_obj");
	assert(r_set[0] == 0.0f);
	if (N > 1) assert(r_set[1] == 10.0f);
	std::cout << "[PASS] set_obj<float>(vals) => " << r_set[0] << std::endl;

	auto m_set = mipp::set_k_obj<float>(kvals);
	static_assert(std::is_same<decltype(m_set), mipp::Rvm<float, 1>>::value, "Type mismatch for set_k_obj");
	assert(m_set[0] == true);
	if (N > 1) assert(m_set[1] == false);
	std::cout << "[PASS] set_k_obj<float>(kvals) => " << m_set[0] << std::endl;

	// 10g. load_obj (aligned)
	auto r_load = mipp::load_obj<float>(vals);
	static_assert(std::is_same<decltype(r_load), mipp::Rvd<float, 1>>::value, "Type mismatch for load_obj");
	assert(r_load[0] == 0.0f);
	std::cout << "[PASS] load_obj<float>(vals) => " << r_load[0] << std::endl;

	// 11. Mask operator overloads (&, &=, |, |=, ^, ^=, ~, !)
	mipp::Rvm<float, 1> m1(true);
	mipp::Rvm<float, 1> m0(false);

	// 11a. Bitwise AND
	auto m_and = m1 & m0;
	assert(m_and[0] == false);
	auto m_and2 = m1 & true;
	assert(m_and2[0] == true);
	auto m_and3 = false & m1;
	assert(m_and3[0] == false);
	m1 &= false;
	assert(m1[0] == false);
	m1 = true;
	std::cout << "[PASS] Rvm & and &= operators verified" << std::endl;

	// 11b. Bitwise OR
	auto m_or = m1 | m0;
	assert(m_or[0] == true);
	auto m_or2 = m0 | false;
	assert(m_or2[0] == false);
	auto m_or3 = true | m0;
	assert(m_or3[0] == true);
	m0 |= true;
	assert(m0[0] == true);
	m0 = false;
	std::cout << "[PASS] Rvm | and |= operators verified" << std::endl;

	// 11c. Bitwise XOR
	auto m_xor = m1 ^ m0;
	assert(m_xor[0] == true);
	auto m_xor2 = m1 ^ true;
	assert(m_xor2[0] == false);
	auto m_xor3 = false ^ m0;
	assert(m_xor3[0] == false);
	m1 ^= true;
	assert(m1[0] == false);
	m1 = true;
	std::cout << "[PASS] Rvm ^ and ^= operators verified" << std::endl;

	// 11d. Bitwise NOT and Logical NOT (~ and !)
	auto m_not = ~m1;
	assert(m_not[0] == false);
	auto m_not0 = ~m0;
	assert(m_not0[0] == true);
	auto m_bang = !m1;
	assert(m_bang[0] == false);
	auto m_bang0 = !m0;
	assert(m_bang0[0] == true);
	std::cout << "[PASS] Rvm ~ and ! operators verified" << std::endl;

	// 11e. Free functions without _k on Rvm (andb, orb, xorb, notb, get)
	auto fn_and = mipp::andb(m1, m0);
	assert(fn_and[0] == false);
	auto fn_or  = mipp::orb(m1, m0);
	assert(fn_or[0] == true);
	auto fn_xor = mipp::xorb(m1, m0);
	assert(fn_xor[0] == true);
	auto fn_not = mipp::notb(m1);
	assert(fn_not[0] == false);
	auto val_get = mipp::get(m1, 0);
	assert(val_get != 0);
	std::cout << "[PASS] Rvm free functions without _k (andb, orb, xorb, notb, get) verified" << std::endl;

	std::cout << "\nAll 11 interoperability, _obj initializer, and Rvm operator tests PASSED successfully!" << std::endl;
	return 0;
}

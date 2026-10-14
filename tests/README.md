# MIPP Tests

Catch2 v3 unit tests of MIPP. The sources in `src/c/`, `src/cpp/` and `src/obj/`
are generated: run `./gen_mipp_headers.py` and `./gen_mipp_tests.py` from
`../generator/` first.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_UNITY_BUILD=ON -DCMAKE_CXX_FLAGS="-march=native"
cmake --build build -j4
./build/bin/run-tests
```

Build options, test filters, `N_ITER` and testing on other targets are described
in the Developer Guide: https://aff3ct.github.io/MIPP/developer/setup/

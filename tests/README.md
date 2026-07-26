# MIPP Tests

Be sure to have generated the MIPP headers and the tests sources first. To do 
so, follow the `README.md` file in the `$root/generator/` folder. The tests are 
written with the Catch2 v3 API.

Install Catch2 on Ubuntu 24.04 LTS:
```bash
sudo apt install catch2
```

To compile the tests:
```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_UNITY_BUILD=ON -DCMAKE_CXX_FLAGS="-Wall -Wno-unused-function -funroll-loops -finline-functions -march=native" -DCMAKE_EXE_LINKER_FLAGS="-static -static-libgcc -static-libstdc++"
cmake --build build -j 4
```

To run the tests:
```bash
./build/bin/run-tests
```

## Build Acceleration & Optimization

1. **Precompiled Headers (PCH)**: `tests/CMakeLists.txt` automatically uses PCH 
   to accelerate header parsing.

2. **Unity Build (Fastest Compilation)**: Pass `-DCMAKE_UNITY_BUILD=ON` to CMake 
   to group test translation units and speed up build by up to 7x (55s vs 401s):
   ```bash
   cmake -B build -DCMAKE_UNITY_BUILD=ON 
   cmake --build build -j4
   ```

## Test Execution Options

- **`N_ITER` Environment Variable**: Controls the number of random test iterations per test function (default is `10`):
  ```bash
  # Run 100 iterations per test for intensive verification
  N_ITER=100 ./build/bin/run-tests

  # Fast sanity run with 1 iteration per test
  N_ITER=1 ./build/bin/run-tests
  ```


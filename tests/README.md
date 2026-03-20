# MIPP Tests

Be sure to have generated the MIPP headers first. To do so, follow the 
`README.md` file in the `$root/generator/` folder.

The to compile the tests:
```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -funroll-loops -finline-functions -march=native" -DCMAKE_EXE_LINKER_FLAGS="-static -static-libgcc -static-libstdc++"
cmake --build build -j 4
```

To run the tests:
```bash
./build/bin/run-tests
```

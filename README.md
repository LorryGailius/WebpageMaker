# WebpageMaker

## How to build
Run these commands in directory containing CMakeLists.txt
```powershell
cmake -D CMAKE_C_COMPILER=<path_to_gcc> -G "MinGW Makefiles" -S . -B build/
cd build
mingw32-make
```

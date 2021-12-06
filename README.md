# WebpageMaker

## How to build
run these commands:

```powershell
cmake -D CMAKE_C_COMPILER=<path_to_gcc> -G "MinGW Makefiles" -S . -B build/
cd build
mingw32-make
```

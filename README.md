# __Web page maker__
This program allows you to create a custom timline website
## __How to use__
When launching this application, provide a file with data about the timeline:
```powershell
./WebPageMaker.exe data.txt
```
## __Data file format__

### Data file contents ###
The data file should contain the following data:
- Timeline title
- Timeline description
- Information about each timepoint 

### Data format ###
Each piece of information should be separated by a **semicolon**
```
title;description;
timepoint_title1;timepoint_description1;timepoint_photo1;
timepoint_title2;timepoint_description2;timepoint_photo2;
timepoint_title3;timepoint_description3;timepoint_photo3;
...
```

### Alternate behaviors ###
Entering a **'-'** into a slot will not show the particular slot on a page:
```
title;description;
-;timepoint_description1;timepoint_photo1;
timepoint_title2;timepoint_description2;-;
timepoint_title3;-;timepoint_photo3;
...
```



## __How to build__
If trying to compile from github repository, CMake is required, use `winget install CMake` in powershell. 
If CMake is already installed run these commands in directory containing **CMakeLists.txt**
```powershell
cmake -D CMAKE_C_COMPILER=<path-to-gcc> -G "MinGW Makefiles" -S . -B build/
cd build
mingw32-make
```

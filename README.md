# __Web page maker__
This program allows you to create a custom timline website
## __How to use__
When launching this application, provide a file with data about the timeline:
```powershell
./WebPageMaker data.txt
```
## __Data file format__

### data file contents ###
The data file should contain the following data:
- Timeline title
- Timeline description
- Information about each timepoint 

### data format ###
Each piece of information should be separated by a semicolon
```
title;description;
timepoint_title1;timepoint_description1;timepoint_photo1;
timepoint_title2;timepoint_description2;timepoint_photo2;
```

## __How to build__
Run these commands in directory containing CMakeLists.txt
```powershell
cmake -D CMAKE_C_COMPILER=<path-to-gcc> -G "MinGW Makefiles" -S . -B build/
cd build
mingw32-make
```

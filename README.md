# __Web page maker__
This program allows you to create a custom timeline website
## __How to use__
When launching this application, provide a data file name as a parameter:
```powershell
./WebPageMaker.exe data.txt
```
## __Data file format__

### Data file contents ###
The data file should **always** contain the following data:
- Timeline title
- Timeline description

### Additional info ###
The program works by parsing different data on a single time point. Each data segment (after Title and Description) is considered the data of a particular time point. Each time point ***requires*** specific data:
- Time point name (ex. `2020`, `Christmas`, etc.)
- Time point description (ex. `The year of a pandemic`, `Christmas is an annual festival`, etc.)
- Time point image (ex. `1.jpg`, `718110.png`, etc.)

**Incorrectly entered data leads to undefined behavior**
**Make sure to read correct data examples below**

### Data format ###
Each piece of information should be separated by a **semicolon**
```
Title;Description;
Timepoint_title1;Timepoint_description1;Timepoint_photo1;
Timepoint_title2;Timepoint_description2;Timepoint_photo2;
Timepoint_title3;Timepoint_description3;Timepoint_photo3;
...
```

### Alternate behaviors ###
Entering a `-` into a slot will not show the particular slot on a page:
```
Title;Description;
Timepoint_title1;-;Timepoint_photo1;
Timepoint_title2;Timepoint_description2;-;
-;Timepoint_description3;Timepoint_photo3;
-;-;-;
...
```

Leaving all three slots empty `-;-;-;` will move the next post to the same side as the previous
```
Title;Description;
Timepoint_title1;Timepoint_description1;Timepoint_photo1; <- is left
-;-;-; <- empty block
Timepoint_title3;Timepoint_description3;Timepoint_photo3; <- is left as well
...
```

`Timeline Title` and `Timeline Description` can also be left blank (`-;-;`), in result no header will be created.

## __How to build__
If trying to compile from github repository, CMake is required, use `winget install CMake` in powershell. 
If CMake is already installed run these commands in directory containing **CMakeLists.txt**
```powershell
cmake -D CMAKE_C_COMPILER=<path-to-gcc> -G "MinGW Makefiles" -S . -B build/
cd build
mingw32-make
```

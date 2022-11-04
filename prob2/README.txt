#README

#Requirements
required OS: Windows 10, 11
required Compiler: Microsoft Visual C++ (MSVC) 14.34
required Visual Studio version: 2022
required build tool: Visual Studio 2022(v143)

#How to compile
1. open proj2.sln file in proj2 directory with Visual Studio2022
2. before run build, please make sure following things
    - set build options to “Release” and for “x64”
    - Windows SDK version 10.0.0(latest)
    - C++ language standard is ISO C++14 Standard
    - platform tool set is Visual Studio 2022(v143)
3. click “build” tab at left up side on your Visual Studio application window
4. click “solution build” option
5. check the successful build message on output window


#How to execute
1. go to “x64” directory in the “proj2” directory
2. go to “Release” directory in “x64” directory
3. you will find execution file named “prob2”
4. open that file.
5. then you can enter the matematical expression as (positive integer)(space)(operator)(space)(positive integer).
   and you will see the calculated result.
   If you want to stop calculating, enter 0. Then the prompt will be closed.
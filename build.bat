@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
set compilerflags=/Fo"./obj/" -std:c++20 /Od /Zi /EHsc /W3 /MDd /I"E:/boost/boost_1_82_0/"^
 /I"E:\JeanProjects\JeanSlnVS19\BaseNumericalTypes" /I"E:\JeanProjects\JeanSlnVS19\SfxBase19"
set linkerflags=/OUT:helloworld.exe /LIBPATH:"E:\JeanProjects\JeanSlnVS19\bin" /LIBPATH:"E:/Boost/boost_1_82_0/lib64-msvc-14.2/"
cl.exe  %compilerflags% *.cpp Classes/*.cpp TestFiles/*.cpp Testcpp17/*.cpp Testcpp20/*.cpp AmazonTest/*.cpp^
 /link %linkerflags% BaseNumericalTypesd.lib
@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
set compilerflags=/Fo"./obj/" -std:c++20 /Od /Zi /EHsc /W3 /MTd /I"C:/Boost/boost_1_84_0/" /I"C:\JeanTests\CPPTestsVS22\ProjectVS22\BaseNumTypes"
set linkerflags=/OUT:helloworld.exe /LIBPATH:"C:\JeanTests\CPPTestsVS22\ProjectVS22\bin" /LIBPATH:"C:\Boost\boost_1_84_0\lib64-msvc-14.3\"
cl.exe /D_SCL_SECURE_NO_WARNINGS %compilerflags% *.cpp Classes/*.cpp TestFiles/*.cpp Testcpp17/*.cpp /link %linkerflags% BaseNumTypesd.lib
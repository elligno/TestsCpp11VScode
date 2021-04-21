@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set compilerflags=/Fo"./obj/" /Od /Zi /EHsc /W3 /MTd /I"C:/Boost/boost_1_60_0/" /I"C:\JeansTests\TestVS2015\ProjectsVS15\BaseNumTypes/"
set linkerflags=/OUT:helloworld.exe /LIBPATH:"C:/JeansTests/TestVS2015/ProjectsVS15/bin/" /LIBPATH:"C:\Boost\boost_1_60_0\lib64-msvc-14.0\"
cl.exe /D_SCL_SECURE_NO_WARNINGS %compilerflags% *.cpp Classes/*.cpp TestFiles/*.cpp /link %linkerflags% BaseNumTypesd.lib
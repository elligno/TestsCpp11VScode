@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc "-IC:/Boost/boost_1_60_0/" 
set linkerflags=/OUT:helloworld.exe
cl.exe %compilerflags% helloworld.cpp JeanTestBatch.cpp^
 testAddFile.cpp Classes/Class2test.cpp TestFiles/QuizQuestions.cpp /link %linkerflags%
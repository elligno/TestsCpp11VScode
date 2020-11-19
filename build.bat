@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc /W3 /MTd /I"C:/Boost/boost_1_60_0/" /I"C:\JeansTests\TestVS2015\ProjectsVS15\BaseNumTypes" /I"${workspaceFolder}/" 
set linkerflags=/OUT:helloworld.exe /LIBPATH:"C:\JeansTests\TestVS2015\ProjectsVS15\bin\"
cl.exe %compilerflags% helloworld.cpp JeanTestBatch.cpp myClass.cpp Classes/Class2test.cpp TestFiles/QuizQuestions.cpp^
 /link %linkerflags% BaseNumTypesd.lib
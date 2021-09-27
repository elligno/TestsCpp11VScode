#pragma once 

// C++ includes
  #include <iostream>
#include <mutex>
#include <fstream>

namespace vs11 
{
    std::mutex logMutex;

    template<class T, class ... Args>
    void fun( const T& first, const Args& ... rest)
    {
        std::cout << "Implementing variadic template\n";
    }
   // https://raymii.org/s/snippets/Cpp_create_and_write_to_a_CSV_file_with_a_variadic_template.html

    bool fileExists( std::string &fileName)
    {
        return static_cast<bool>(std::ifstream(fileName));
    }

    template <typename filename, typename Arg>
    void writeFile( filename &fileName, Arg arg)
    {
        std::lock_guard<std::mutex> csvLock(logMutex);
        std::fstream file;
        file.open(fileName, std::ios::out | std::ios::app);
        if (file)
            file << arg;
    }

    template <typename filename, typename First, typename... Args>
    void writeFile( filename &fileName, First first, Args... args)
    {
        writeFile(fileName, first);
        writeFile(fileName, args...);
    }

    int main()
    {
        std::string theFile = "a";
        if (!fileExists(theFile))
            writeFile(theFile, "\"header1\",", "\"header2\",", "\"header3\"", "\n");
        writeFile(theFile, "\"data1\",", "\"data2\",", "\"data3\"", "\n");
        writeFile(theFile, "\"second1\",", "\"second2\",", "\"second3\"", "\n");
        return 0;
    }
} // End of namespace
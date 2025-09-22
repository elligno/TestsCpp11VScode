#include <cassert>
#include <iostream>
#include <fstream>
#include <string_view>
#include <filesystem>
#include <cstdlib> // for what??

namespace cpp17 
{
    // file system is part of C++17
    // file system its something that i need to master perfectly
    // Test the following
    //   create directories
    //   working directory (default)
    //   using helper functions such as: status, error code
    //   directory iterator (retrieving element in a directory)
    //   list files in a directory
    //   traverse folder to check file or ...
    void testStdFilesystem() 
    {
        std::cout << "Starting to test std file system\n";

        // make code cleqaner
        namespace fs = std::filesystem;
        
        // let's start by creating a folder
        // just a check "C:\JeanTests\VSCodeWork\BasicTest"
        auto w_currPath = fs::current_path(); // path of the current file? is it?
        auto w_pathAbs = w_currPath.is_absolute();  // ???

        using namespace std::string_view_literals;
        auto w_myPath = R"(C:\JeanTests\VSCodeWork\BasicTest)"sv;
        fs::path w_path2cmp{w_myPath}; // take a string view
        // a function call equivalent (both point to the same file?)
        if( fs::equivalent(w_currPath, w_path2cmp)) 
        {
            std::cout << "Path refer to same file\n";
            std::cout << "path element of \"" << w_path2cmp.string() << "\":\n";
            for( fs::path elem : w_path2cmp) // traverse path elelement
            {
                std::cout << " \"" << elem.string() << '"';
            }
        }
        
        // set current path to user path defined (from string view)
        fs::current_path(w_myPath);  // ...
        fs::path w_testdir{"tmp/test"};  // created in the current dir?
        
        // create directories tmp/test if they don't exist
        auto isCreated = fs::create_directories(w_testdir);
        if(!create_directories(w_testdir))
        {
            std::cout << "\" " << w_testdir.string() << "\" already exists\n"; 
        }
        
        // create data file text file in tesDir
        auto w_testFile = w_testdir/"dataFile.txt";
        std::ofstream w_dataF{w_testFile};
        if (!w_dataF)
        {
            std::cerr << "OOPS can't open \"" << w_testFile.string() << "\"\n";
            std::exit(EXIT_FAILURE); // exit program with failure         
        }   

         // create a switch case to check
          switch (fs::status(w_testFile).type())
          {
          case fs::file_type::regular:
              std::cout << "we have aa regular file\n";
              std::cout << "file name is: " << w_testFile.lexically_normal().string();
              break;
          case fs::file_type::directory:
              std::cout << "we have a directory\n";
              break;
          case fs::file_type::not_found:
              std::cout << "we couldn't found the file\n";
              break;
              case fs::file_type::unknown:
              std::cout << "we couldn't identify type of file";
              break;
          default:
              break;
         }

         auto begDir = fs::directory_iterator{w_testdir}; // begin 
         auto endDir = fs::directory_iterator{}; // end
         auto anyFileIn = std::distance(begDir,endDir);

        auto fileStatus = begDir->status();
        std::u8string w_u8str = begDir->path().u8string();
        bool dirOk = fs::is_directory(begDir->status());
        auto retPaths = begDir->path();

         // just a check where I'm at?
         auto checkPath = fs::current_path(); // expect root
         auto rootPath = checkPath.root_directory();
         auto rootok = checkPath.has_root_directory();
         auto rootName = checkPath.has_root_name();
         // list all files in directory
         for( const auto& dirEntry : begDir)
         {
            if(dirEntry.is_directory())
              std::cout << " ";
              else if(dirEntry.is_regular_file())
               std::cout << "replace file name, but how??\n";
               else
               std::cout << "whatever";
         }
         

         if( fs::exists("dataFile.txt")) // check if file exist?
         {
            /* code */
         }

         // other test: filel system dxceptionand error code
         //  
         try
         {
            /* code */
         }
         catch(const fs::filesystem_error::exception& e)
         {
            std::cerr << e.what() << '\n';
            // how do we use error code?
           // fs::filesystem_error::code
         }
         
    }
} // End of namespace
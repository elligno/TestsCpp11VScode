
#pragma once

// C++ includes
#include <algorithm>
#include <filesystem> // C++17 file system

namespace jb
{
    // searching for a file in a directory
    bool FindFile( const std::filesystem::path& aPath2Look, // path to start from
        std::filesystem::path& aPat, // path of found file
        std::string_view aFileName2Look) //file name to look for (cheap to copy)
    {
        namespace fs = std::filesystem;
        
        bool foundFile=false;
        // declare local variable
        const fs::path file{aFileName2Look}; // file found
        auto w_fileLook4 = aFileName2Look;
        // declare recursive_directory_iterator (beg|end)
        const fs::recursive_directory_iterator begDir{aPath2Look};
        const fs::recursive_directory_iterator endir{};
        // stl algorithm find_if (pass a lambda to check file)
        auto foundOne = std::find_if(begDir, endir, 
        [&file] ( fs::directory_entry& aFile2Check) // why capture by ref?
        {
            // check path equality
            return (file == aFile2Check.path().filename());
        });

        // once find it, 
        if (foundOne!=endir)
        {
            foundFile=true;
            aPat=foundOne->path();
        }        
       return foundFile;
    }
} // namespace jb
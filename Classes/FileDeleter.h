
#pragma once

// C++ includes
#include <string>
#include <fstream>
#include <memory>
#include <cstdio>

namespace vs11 
{
    /**
     * @brief Helper to close and delete temporary file 
     * 
     * Usage:
     *   std::shared_ptr<std::ofstream> w_ptr2File{ new std::ofstream{"Tmp.txt"},
     *                    FileDeleter{"Tmp.txt"} };
     *   
     */
    class FileDeleter 
    {
      private:
        std::string m_filename;
      public:
      /**
       * @brief As usaual for types with value semantic, the best way constructor
       *        initialize members with move (direct list initalization)
       * 
       * @param aFilename 
       * @return 
       */
      FileDeleter( std::string aFilename) : m_filename { std::move(aFilename) } {}
      void operator() ( std::ofstream* fp)
      {
         fp->close();                      // close file
         std::remove( m_filename.c_str()); // delete file 
      }
    };
} // End of namespace 
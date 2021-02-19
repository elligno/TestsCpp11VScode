
#pragma once

// C++ includes
#include <iostream>
// STL include
#include <vector>
// boost include
//#include <boost/noncopyable.hpp>
#include "Singleton.hpp"

namespace testSfx 
{
	// CRTP (Curious Recursive Template Pattern) idiom
	// See James Coplien book (Advanced C++ idiom and ,,,)
	// Actually it's more a helper to make code a little more
	// readable. Provide basic services by user can populate 
	// with more services depending on its needs.
	// Usage:
	//  as global instance of the program
	//  
	class LoggerUtil : public emcil::Singleton<LoggerUtil>  
	{ 
	public:
		// open file for writing (file name as default)
		void open( const std::string& aFilename = "LoggerCpp11.txt"); 
		bool isOpen() { return m_opened;} // check file status
		void close();  // close when finish writing
		void write2file( const std::string& aMsg=""); // writing to file
		void write2file( const std::string& aMsg, const int aVal);
        void setFileAndPath( const std::string& aFile); // set path or location of this file
		const std::string& getFileLocation() const {return m_filePath;}
		void setWorkingDir( const std::string aDefLoc);
		bool isWorkingDirExist( const std::string& aDefLoc);
		bool findFile(); // search in the current directory

		// First time we call instance() it call the logger default ctor.
		// But the problem is that ctor is protected which cannot be call
		// outside of the method or client. The method instance is static,
		// no this pointer.
		// Friend relationship means that friend class can access private 
		// member of the class, in this case when calling the singleton 
		// for the first time no instance has been created, base class 
		// need to create or call ctor from derived class, since the latter 
		// is protected cannot be accessed from outsider unless we grant 
		// access by using the friend keyword (purpose of this declaration)  
		friend class emcil::Singleton<LoggerUtil>;
	protected:
    // Client have no choice to use the Singleton static method  
		// instance() which manage the creation of the sole instance.
		LoggerUtil(); // logger creation
	private:
		bool m_opened;
		FILE* m_file2write;
		
		// from E. McNeil code
		FILE *FichierDEBUG;
		char NomFichierDEBUG[256];
		// file name, in this case it is set to a default ??
		std::string m_fileName;
		std::string m_filePath;
	}; // class
} // End of namespace
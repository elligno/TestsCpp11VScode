
// C++ includes
#include <utility>
#include <tuple>
// boost include
#include <filesystem>      // std file system utility
// Testcpp include
#include "LoggerUtil.h"

namespace testSfx 
{
	// initialize the static variable 
	//	Hydro1DLogger* Hydro1DLogger::m_sHlogger=nullptr;

	// default ctor
	LoggerUtil::LoggerUtil()
	: m_opened(false), // not open yet
	  FichierDEBUG(nullptr) // not open 
	{
		// opening file
		//	open();
	}
	// closing file
	void LoggerUtil::close()
	{
		// Close FichierDEBUG if it is not NULL 
		if( FichierDEBUG)
		{
			errno_t err = fclose( FichierDEBUG);
			if ( err == 0 )
			{
				printf( "The logger file 'HLL RK2 Debug' was closed\n" );
				FichierDEBUG=nullptr;
				m_opened=false;
			}
			else
			{
				printf( "The logger file 'HLL RK2 Debug' was not closed\n" );
			}
		}
	}
	// 
	void LoggerUtil::open( const std::string& aFilename/*="LoggerCpp11.txt"*/)
	{
		// initializing file creation 
		::strcpy_s( NomFichierDEBUG, 256, aFilename.c_str());

		// Open for write 
		errno_t err = fopen_s( &FichierDEBUG, NomFichierDEBUG, "w" );
		if( err == 0 )
		{
			printf( "The logger file 'LoggerCpp11.txt' was opened\n");
			m_opened=true;
		}
		else
		{
			printf( "The logger file 'LoggerCpp11.txt' was not opened\n");
		}
	}

	void LoggerUtil::write2file( const std::string& aMsg, const int aVal)
	{
		if( aMsg.empty())
		{
			//	Evaluation de F1 et F2
			fprintf( FichierDEBUG, "++++to be completed: %d\n", aVal);
			fprintf( FichierDEBUG, "\n");
		}
	}

	void LoggerUtil::write2file(const std::string& aMsg/*=""*/)
	{
		// write something
		if( aMsg.empty())
		{
			//	
			fprintf( FichierDEBUG, "++++: %s\n", aMsg.c_str());
			fprintf( FichierDEBUG, "\n");
		}
	}

	void LoggerUtil::setFileAndPath(const std::string& aFile)
	{
    // what we do  here? maybe using the boost file system 
		// to check and rename/copy file, something like this
		// By default if we don't set any thing, where file is saved?

		// set namespace for clarity
		namespace bfs = std::filesystem;
		bfs::path w_currentPath;
		w_currentPath = bfs::current_path();
		m_filePath = w_currentPath.string();

		// using Boost string library to 
		const std::string w_rootDir(m_filePath);
		
		// current dir??
		std::string w_pathStr( w_rootDir+aFile);

		// 	const std::string w_fileName("AdvanceAlgo.txt");
		// //	bfs::path w_dir(w_pathStr);
		// 
		// 	// create it 
		// // 	if( bfs::create_directory(w_dir))
		// // 		std::cout << "Success" << "\n";
		// 

		// find recursively a file in a directory
		bfs::path w_SearchDir( w_currentPath); // looking into
		bfs::path w_DirContainingFile; // returned 
		bfs::path w_SearchFile( aFile);  
		
		// 
		// 	if( FindFile( w_SearchDir, w_DirContainingFile, w_fileName))  
		// 	{  
		// 		std::cout << "File location:" << std::endl;  
		// 		std::cout << w_DirContainingFile.string();  
		// 	}  
		// 
		// 	// check if we found something
		// 	if( w_DirContainingFile.empty())
		// 	{
		// 		// default file to read or algorithm as default 
		// 		// to run the simulation (to be completed) 
		// 		std::cerr << "Problem with config file for algo\n";
		// 	}
		// 	else
		// 	{
		// 		// otherwise just 
		// 		std::ifstream w_algoNameFile( w_DirContainingFile.string(), 
		// 			std::ifstream::basic_ios::in);
		// 		// now 
		// 		while( !w_algoNameFile.eof())
		// 		{
		// 			w_algoNameFile >> w_nameAlgo;
		// 
		// 			// create list of numerical treatment algorithm 
		// 			// add it to the list
		// 			g_NumTreatmentName.push_back( w_nameAlgo);
		// 		}
		// 	}
		//#endif
	}

	void LoggerUtil::setWorkingDir( const std::string aDefaultLoc)
	{
		// set namespace for clarity
		namespace bfs = std::filesystem;

		// retrieve current directory
		bfs::path w_currentPath;
		w_currentPath = bfs::current_path();

		// check if the directory exist
		bfs::path w_dir(w_currentPath);
		w_dir+=aDefaultLoc;

		// create it 
// 		if( bfs::create_directory(w_dir))
// 				std::cout << "Success" << "\n";

		try  
		{  
			if( std::filesystem::exists(w_dir))  
			{  
				std::cerr << "Destination directory "   
					<< w_dir.string()  
					<< " already exists." << '\n';  
			//	return false;  
			}  

			// Create the destination directory  
			if( !std::filesystem::create_directory(w_dir))  
			{  
				std::cerr << "Unable to create destination directory"  
					<< w_dir.string() << '\n';  
		//		return false;  
			}  
		}  // try 
		catch( std::filesystem::filesystem_error const & e)  
		{  
			std::cerr << e.what() << '\n';  
			//return false;  
		} 
	}

	bool LoggerUtil::isWorkingDirExist(const std::string& aDefLoc)
	{
		bool ret = false;
		try  
		{  
			// Check whether the function call is valid  
			if( !std::filesystem::exists(aDefLoc) ||  
				!std::filesystem::is_directory(aDefLoc))  
			{  
				std::cerr << "Source directory "   
					<< aDefLoc.c_str()
					<< " does not exist or is not a directory."   
					<< '\n';  
				ret=false;  
			}  
		}  // try 
		catch( std::filesystem::filesystem_error const & e)  
		{  
			std::cerr << e.what() << '\n';  
			ret = false;  
		} 
		return ret;
	}
} // End of namespace


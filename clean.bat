REM =======================================================================
REM Batch (.BAT) script (Windows) to delete all temporary files after
REM  compiling a project with Microsoft Visual Studio (Visual C++) or GCC.
REM 
REM   Warning: It also deletes the debug databases, needed to "step into"
REM    from a debugger. These files may be really *large*, but if you think
REM    you will need them, remove the file for "*.pdb" below.
REM
REM Usage: 
REM  - Open a terminal (Windows-key + R , type "cmd", press ENTER)
REM  - To delete build files from one (or, optionally) more directories, execute: 
REM      delete_build_temps.bat BUILDIR1 [BUILDIR2] [BUILDIR3] [...]
REM
REM By: Jose Luis Blanco Claraco, 2013
REM      Released to Public Domain.
REM
REM Revision history
REM  Jean Belanger (December 2020)
REM   Rename the file by clean.bat
REM    Usage:
REM     ./clean.bat obj
REM    for this VS code project
REM =======================================================================

echo ------------------------------------------------------------
echo About to delete .obj files from path contains.
echo Try ... to be completed
echo ------------------------------------------------------------

set DIR=%CD%

:Loop
IF "%1"=="" GOTO Continue
cd %1
del /s *.obj  
rem del /s *.o  
rem del /s *.pch
rem del /s *.pdb
rem del /s *.ilk
rem del /s *.idb
rem del /s *.gch
SHIFT
cd %DIR%
GOTO Loop
:Continue
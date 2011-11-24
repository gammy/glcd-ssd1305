Instructions for how to build a zip.

(Currently zip builds can only be done in PC environments.)


Generic notes based on current operation:

- The head of the SVN tree is checked out into a working directory
- glcd/debug and glcd/build directories are removed from the working directory
- A "manifest" file is created that has all the SVN information for every file
- All the .svn directories are stripped away
- doxygen documentation is updated.
- All other files and directories are left "as is".
 (No other files like word docs are touched, modified, or removed)

The zip image will land in the same directory where the build script located.
The zip image name will include the date.


PC environement builds
=======================
(See the mkzip.bat file for full details)
First make sure all the proper tools are installed:
 # Needed Tools:
 # -------------
 # you must have a commandline SVN tool:
 #	http://www.open.collab.net/downloads/subversion/
 #
 # you must have 7zip installed.
 #	http://www.7-zip.org/
 # 	Make sure to manually add the install dir to your path as the
 #	default install does not do this.
 # 	normally it is: $SystemDrive:\Program Files\7-Zip
 #
 # you must have doxygen/doxywizard installed.
 #	http://www.doxygen.nl/download.html#latestsrc
 #	(Make sure to have version 1.6.3 or later)
 #


Once the tools are in place you can simply double click on the mkzip.bat file.
The script will occasionally prompt for input.
This is to allow inspection of directories.

If something is going wrong and the cmd windows is going away
before any error message can be read,
use runmkzip.bat instead.
The only diference is taht runmkzip.bat is a wrapper that will
pause after mkzip finishes so the command window will automatically
go away on a fatal batch processing error.

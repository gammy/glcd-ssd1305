@echo off
REM ##################################################################
REM # Windows batch file to create GLCD distribution zip image.
REM #
REM # This batch file has 2 modes
REM # 
REM # 1) If called with no argument, use SVN to checkout a "working"
REM #
REM # 2) If called an argument, use that directory as the source
REM #    to create a "working" directory.
REM #    The directory indicated will be copied to the working directory.
REM #    This method can be used with Windows Drag-n-Drop.
REM #    Simply drag a development SVN glcd directory on top of
REM #    of the batch file and it will create a zip file based on that
REM #    glcd tree rather than grabbing a new from the head of SVN
REM #
REM #
REM # Needed Tools:
REM # -------------
REM # you must have a commandline SVN tool:
REM #	http://www.open.collab.net/downloads/subversion/
REM #
REM # you must have 7zip installed.
REM #	http://www.7-zip.org/
REM # 	Make sure to manually add the install dir to your path as the
REM #	default install does not do this.
REM # 	normally it is: $SystemDrive:\Program Files\7-Zip
REM #
REM # you must have doxygen/doxywizard installed.
REM #	http://www.doxygen.nl/download.html#latestsrc
REM #	(Make sure to have version 1.6.3 or later)
REM #
REM ##################################################################

REM #
REM # set PWD variable (grab it from path of batch file)
REM #

set PWD=%~dp0

REM #
REM # do some REAL ugliness to work around the
REM # @#$%! window long path problem.
REM #
REM # create a substitute drive that points to the
REM # current path.
REM # 

set SUBDRIVE=Q

REM # look for ourselves on the subst drive
REM # if so remove the subst

if exist %SUBDRIVE%:\%~nx0 subst %SUBDRIVE%: /d


subst %SUBDRIVE%: %PWD%\.

if not ERRORLEVEL 1 goto good_subst
echo Fatal error: Could not substitute drive %SUBDRIVE%:
goto done


:good_subst

REM # proceed by changing drive to subtituted drive
REM # and fudging up PWD

%SUBDRIVE%:

set PWD=%SUBDRIVE%:\

REM #
REM # LOG file name
REM #

set LOGFILE=%PWD%\%~n0.log

echo CURRENT WORKING directory: %PWD%

REM #
REM # Setup some date variables
REM #

set MTH=%DATE:~4,2%
set DAY=%DATE:~7,2%
set YR=%DATE:~10,4%
set HR=%TIME:~0,2%
set HR0=%TIME:~0,1%
if "%HR0%"==" " set HR=0%TIME:~1,1%
set MIN=%TIME:~3,2%
set SEC=%TIME:~6,2%
set MYDATE=%YR%%MTH%%DAY%
set MYTIME=%HR%%MIN%%SEC%

REM ##################################################################
REM #
REM # Define working variables
REM #
REM ##################################################################

REM #
REM # name of library
REM # This name will be used for the name of the distribution
REM # directory inside the zip file.
REM # it is the name of the directory that will be in the
REM # arduinoXXX/hardware/libraries
REM #

set GLCDLIBNAME=glcd

REM #
REM # location of GLCD lib SVN repository
REM #

set GLCDREPO=http://arduino-glcd.googlecode.com/svn/trunk/glcd

REM #
REM # SVN commands
REM #
set SVNCMD=svn checkout
set SVNINFO=svn info
set SVNLIST=svn list -vR

REM #
REM # zip command
REM #
set ZIPCMD=7z a


REM #
REM # Name of working directory for distibution tree
REM #  note/warning the path needs to be full vs relative
REM #  as svn has special code to deal with the @#@$@! 
REM #  windows long path issue but it only kicks in on absolute paths.
REM #
set GLCDDISTDIR=%PWD%\%GLCDLIBNAME%


REM #
REM # Doxygen command and config file stuff
REM #  note: doxygen must be started in the directory
REM #  where the config file is since all paths in the config file
REM #  are relative to that point.
REM #

set DOXYGEN=doxygen
set DOXYGENDIR= %GLCDDISTDIR%\doc
set DOXYGENCFG=Doxyfile

REM #
REM # Name of ZIP file
REM # has date as part of file name
REM #
set GLCDZIPNAME=%GLCDLIBNAME%-%MYDATE%.zip

REM #
REM # name of manifest file
REM #
set GLCDMANIFEST=%GLCDDISTDIR%\manifest.txt

REM ##################################################################
REM # Now start to actually do something

echo Starting build %DATE% %TIME% >%LOGFILE%

REM # check to see if there is an argument from drag-n-drop
REM # if no argument passed in, then get files from SVN

if [%1]==[] goto get_svnfiles

echo Drag and drop mode for file %1

echo Copying existing devlopment tree
REM DO NOT TURN THIS ON
REM echo copy %1 %GLCDDISTDIR%
echo DRAG and DROP not yet supported
pause
goto done
goto working_tree_ready


:get_svnfiles
echo Checking out SVN working tree
echo ======== Checkout SVN tree >> %LOGFILE%
%SVNCMD% %GLCDREPO% %GLCDDISTDIR% >>%LOGFILE%

:working_tree_ready

echo Building Doxygen Documents
echo ======== Building Doxygen Documents >> %LOGFILE%
cd %DOXYGENDIR%
%DOXYGEN% %DOXYGENCFG%  >> %LOGFILE% 2>&1
cd %PWD%

echo Creating SVN Manifest file
echo Distribution files created %DATE% %TIME% >%GLCDMANIFEST%
echo =====================================================================>>%GLCDMANIFEST%
cd %GLCDDISTDIR%
%SVNINFO% >>%GLCDMANIFEST%
echo =====================================================================>>%GLCDMANIFEST%
%SVNLIST% >>%GLCDMANIFEST%
cd %PWD%

echo Removing SVN control files
cd %GLCDDISTDIR%
for /D /r %%G in (.svn) DO rmdir /S /Q %%G
cd %PWD%

echo Creating Zip file
echo ======== Creating Zip file >> %LOGFILE%
erase /F %GLCDZIPNAME%
%ZIPCMD% %GLCDZIPNAME% %GLCDDISTDIR% >> %LOGFILE%

echo Removing SVN working tree
rmdir /S /Q %GLCDDISTDIR%


REM remove substituted drive

subst %SUBDRIVE%: /d

:done
pause

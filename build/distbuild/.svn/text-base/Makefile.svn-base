##############################################################
# Makefile to build the glcd library distribution
#
# build process overview:
#
# - Checkout a glcd library from SVN
# - Copy that glcd SVN directory to a tmp/working directory
# - Remove the SVN tracking stuff from the working directory
# - update/create any needed documenation in the working directory
# - remove any uneeded/unwanted subdirectories from the working directory
# - create a zip file of the working directory.
#
# Build requires SVN na 7zip command line tools
#
############################################################
#
# Windoze users:
#
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



#
# name of library
# This name will be used for the name of the distribution
# directory inside the zip file.
# it is the name of the directory that will be in the
# arduinoXXX/hardware/libraries
#
GLCDLIBNAME = glcd

# location of GLCD lib SVN repository

GLCDREPO = http://arduino-glcd.googlecode.com/svn/trunk/glcd

SVNCMD = svn checkout
RM = rm -f
RMDIR = rm -rf
CPDIR = cp -r

ZIPCMD = 7z a

#
# list of unwanted directories
# these are all relative the top level library directory
# i.e. "glcd" 
#
GLCDUNWANTED = debug build

# files/directories that no matter where they are,
# remove them from the GLCD dist directory
# be careful with this.

GLCDTRASH = .svn


# Name of SVN tree where checkout will occur
GLCDSVNDIR = $(PWD)/svn$(GLCDLIBNAME)

# Name of working directory for distibution tree
GLCDDISTDIR = $(PWD)/$(GLCDLIBNAME)

#
# Name of ZIP file
# has date as part of file name
#
GLCDZIPNAME = $(GLCDLIBNAME).zip


all: docs distzip

svndir: $(GLCDSVNDIR)
distdir: $(GLCDDISTDIR)
distzip: $(GLCDZIPNAME)

docs: $(GLCDDISTDIR)
	echo building documents

clean:
	$(RMDIR) $(GLCDSVNDIR)
	$(RMDIR) $(GLCDDISTDIR)
	$(RMR) *.zip

$(GLCDSVNDIR):
	$(SVNCMD) $(GLCDREPO) $@

$(GLCDDISTDIR): $(GLCDSVNDIR)
	$(CPDIR) $(GLCDSVNDIR) $@
	for trash in $(GLCDTRASH); do\
		find $@ -name $$trash -depth -exec rm -rf '{}' ';' ;\
	done
	for unwanted in $(GLCDUNWANTED); do\
		rm -rf $@/$$unwanted ;\
	done

$(GLCDZIPNAME): $(GLCDDISTDIR)
	$(RM) $@
	$(ZIPCMD) $@ $(GLCDDISTDIR)


dummy:
	echo $(PWD)

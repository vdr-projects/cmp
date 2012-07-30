#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Picture.o \
	${OBJECTDIR}/src/Audio.o \
	${OBJECTDIR}/src/DVDImage.o \
	${OBJECTDIR}/src/VdrRecording.o \
	${OBJECTDIR}/src/MediaFactory.o \
	${OBJECTDIR}/src/LegacyVdrRecording.o \
	${OBJECTDIR}/src/MediainfoReader.o \
	${OBJECTDIR}/src/FSMediaScanner.o \
	${OBJECTDIR}/src/AbstractMultiFileMovie.o \
	${OBJECTDIR}/src/AbstractMedia.o \
	${OBJECTDIR}/src/Movie.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=gnu++0x -fomit-frame-pointer -fPIC -pthread -Wall -Wno-parentheses -Wno-switch -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=implicit-function-declaration
CXXFLAGS=-std=gnu++0x -fomit-frame-pointer -fPIC -pthread -Wall -Wno-parentheses -Wno-switch -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=implicit-function-declaration

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

${OBJECTDIR}/src/Picture.o: src/Picture.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Picture.o src/Picture.cc

${OBJECTDIR}/src/Audio.o: src/Audio.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Audio.o src/Audio.cc

${OBJECTDIR}/src/DVDImage.o: src/DVDImage.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DVDImage.o src/DVDImage.cc

${OBJECTDIR}/src/VdrRecording.o: src/VdrRecording.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/VdrRecording.o src/VdrRecording.cc

${OBJECTDIR}/src/MediaFactory.o: src/MediaFactory.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaFactory.o src/MediaFactory.cc

${OBJECTDIR}/src/LegacyVdrRecording.o: src/LegacyVdrRecording.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LegacyVdrRecording.o src/LegacyVdrRecording.cc

${OBJECTDIR}/src/MediainfoReader.o: src/MediainfoReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediainfoReader.o src/MediainfoReader.cc

${OBJECTDIR}/src/FSMediaScanner.o: src/FSMediaScanner.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FSMediaScanner.o src/FSMediaScanner.cc

${OBJECTDIR}/src/AbstractMultiFileMovie.o: src/AbstractMultiFileMovie.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractMultiFileMovie.o src/AbstractMultiFileMovie.cc

${OBJECTDIR}/src/AbstractMedia.o: src/AbstractMedia.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractMedia.o src/AbstractMedia.cc

${OBJECTDIR}/src/Movie.o: src/Movie.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../networking/include -I../IO/include -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Movie.o src/Movie.cc

# Subprojects
.build-subprojects:
	cd ../vdr && ${MAKE}  -f Makefile CONF=Debug
	cd ../util && ${MAKE}  -f Makefile CONF=Debug
	cd ../networking && ${MAKE}  -f Makefile CONF=Debug
	cd ../IO && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

# Subprojects
.clean-subprojects:
	cd ../vdr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../networking && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../IO && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

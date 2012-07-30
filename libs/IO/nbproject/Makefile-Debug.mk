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
	${OBJECTDIR}/src/CommandReader.o \
	${OBJECTDIR}/src/FileRepresentation.o \
	${OBJECTDIR}/src/LineReader.o \
	${OBJECTDIR}/src/File.o \
	${OBJECTDIR}/src/Reader.o \
	${OBJECTDIR}/src/ConfigReader.o \
	${OBJECTDIR}/src/FileReader.o \
	${OBJECTDIR}/src/FileSystem.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a

${OBJECTDIR}/src/CommandReader.o: src/CommandReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommandReader.o src/CommandReader.cc

${OBJECTDIR}/src/FileRepresentation.o: src/FileRepresentation.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileRepresentation.o src/FileRepresentation.cc

${OBJECTDIR}/src/LineReader.o: src/LineReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LineReader.o src/LineReader.cc

${OBJECTDIR}/src/File.o: src/File.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/File.o src/File.cc

${OBJECTDIR}/src/Reader.o: src/Reader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Reader.o src/Reader.cc

${OBJECTDIR}/src/ConfigReader.o: src/ConfigReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConfigReader.o src/ConfigReader.cc

${OBJECTDIR}/src/FileReader.o: src/FileReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileReader.o src/FileReader.cc

${OBJECTDIR}/src/FileSystem.o: src/FileSystem.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D_REENTRANT -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Iinclude -I../util/include -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileSystem.o src/FileSystem.cc

# Subprojects
.build-subprojects:
	cd ../vdr && ${MAKE}  -f Makefile CONF=Debug
	cd ../util && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libio.a

# Subprojects
.clean-subprojects:
	cd ../vdr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../util && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

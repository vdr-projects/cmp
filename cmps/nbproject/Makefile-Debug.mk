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
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/codecTest \
	${TESTDIR}/TestFiles/connectionHandlerTest \
	${TESTDIR}/TestFiles/fileSystemTest \
	${TESTDIR}/TestFiles/fsScanTest \
	${TESTDIR}/TestFiles/jsonTest \
	${TESTDIR}/TestFiles/metaScanTest \
	${TESTDIR}/TestFiles/stringBuilderTest

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
LDLIBSOPTIONS=serverlib/dist/Debug/GNU-Linux-x86/libserverlib.a ../libs/mediaScan/dist/Debug/GNU-Linux-x86/libmediascan.a ../libs/networking/dist/Debug/GNU-Linux-x86/libnetworking.a ../libs/IO/dist/Debug/GNU-Linux-x86/libio.a ../libs/util/dist/Debug/GNU-Linux-x86/libutil.a ../libs/vdr/dist/Debug/GNU-Linux-x86/libvdr.a -lpthread -lrt -lssl -lpcrecpp -lmediainfo

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: serverlib/dist/Debug/GNU-Linux-x86/libserverlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ../libs/mediaScan/dist/Debug/GNU-Linux-x86/libmediascan.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ../libs/networking/dist/Debug/GNU-Linux-x86/libnetworking.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ../libs/IO/dist/Debug/GNU-Linux-x86/libio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ../libs/util/dist/Debug/GNU-Linux-x86/libutil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ../libs/vdr/dist/Debug/GNU-Linux-x86/libvdr.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cc

# Subprojects
.build-subprojects:
	cd serverlib && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/mediaScan && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/networking && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/IO && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/util && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/vdr && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/vdr && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/util && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/networking && ${MAKE}  -f Makefile CONF=Debug
	cd ../libs/IO && ${MAKE}  -f Makefile CONF=Debug
	cd serverlib && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/BaseScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/codecTest: ${TESTDIR}/tests/CodecTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/codecTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/connectionHandlerTest: ${TESTDIR}/tests/ConnectionHandlerTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/connectionHandlerTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/fileSystemTest: ${TESTDIR}/tests/FileSystemTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/fileSystemTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/fsScanTest: ${TESTDIR}/tests/FScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/fsScanTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/jsonTest: ${TESTDIR}/tests/JSonTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/jsonTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/metaScanTest: ${TESTDIR}/tests/MetaScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/metaScanTest $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/stringBuilderTest: ${TESTDIR}/tests/StringBuilderTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/stringBuilderTest $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/BaseScanTest.o: tests/BaseScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/BaseScanTest.o tests/BaseScanTest.cc


${TESTDIR}/tests/CodecTest.o: tests/CodecTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CodecTest.o tests/CodecTest.cc


${TESTDIR}/tests/ConnectionHandlerTest.o: tests/ConnectionHandlerTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ConnectionHandlerTest.o tests/ConnectionHandlerTest.cc


${TESTDIR}/tests/FileSystemTest.o: tests/FileSystemTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/FileSystemTest.o tests/FileSystemTest.cc


${TESTDIR}/tests/FScanTest.o: tests/FScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/FScanTest.o tests/FScanTest.cc


${TESTDIR}/tests/JSonTest.o: tests/JSonTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/JSonTest.o tests/JSonTest.cc


${TESTDIR}/tests/MetaScanTest.o: tests/MetaScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MetaScanTest.o tests/MetaScanTest.cc


${TESTDIR}/tests/StringBuilderTest.o: tests/StringBuilderTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/StringBuilderTest.o tests/StringBuilderTest.cc


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cc 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -Iserverlib/include -I../libs/mediaScan/include -I../libs/networking/include -I../libs/IO/include -I../libs/util/include -I../libs/vdr/include -I. -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cc;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/codecTest || true; \
	    ${TESTDIR}/TestFiles/connectionHandlerTest || true; \
	    ${TESTDIR}/TestFiles/fileSystemTest || true; \
	    ${TESTDIR}/TestFiles/fsScanTest || true; \
	    ${TESTDIR}/TestFiles/jsonTest || true; \
	    ${TESTDIR}/TestFiles/metaScanTest || true; \
	    ${TESTDIR}/TestFiles/stringBuilderTest || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps

# Subprojects
.clean-subprojects:
	cd serverlib && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/mediaScan && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/networking && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/IO && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/vdr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/vdr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/networking && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../libs/IO && ${MAKE}  -f Makefile CONF=Debug clean
	cd serverlib && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

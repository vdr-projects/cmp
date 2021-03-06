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
CND_CONF=Release
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
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps \
	${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cc

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/BaseScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/CodecTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/ConnectionHandlerTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/FileSystemTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/FScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/JSonTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/MetaScanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps: ${TESTDIR}/tests/StringBuilderTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc}   -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/BaseScanTest.o: tests/BaseScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/BaseScanTest.o tests/BaseScanTest.cc


${TESTDIR}/tests/CodecTest.o: tests/CodecTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CodecTest.o tests/CodecTest.cc


${TESTDIR}/tests/ConnectionHandlerTest.o: tests/ConnectionHandlerTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ConnectionHandlerTest.o tests/ConnectionHandlerTest.cc


${TESTDIR}/tests/FileSystemTest.o: tests/FileSystemTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/FileSystemTest.o tests/FileSystemTest.cc


${TESTDIR}/tests/FScanTest.o: tests/FScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/FScanTest.o tests/FScanTest.cc


${TESTDIR}/tests/JSonTest.o: tests/JSonTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/JSonTest.o tests/JSonTest.cc


${TESTDIR}/tests/MetaScanTest.o: tests/MetaScanTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/MetaScanTest.o tests/MetaScanTest.cc


${TESTDIR}/tests/StringBuilderTest.o: tests/StringBuilderTest.cc 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${TESTDIR}/tests/StringBuilderTest.o tests/StringBuilderTest.cc


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cc 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cc;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	    ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cmps

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

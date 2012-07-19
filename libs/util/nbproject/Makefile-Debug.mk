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
	${OBJECTDIR}/src/JSonWriter.o \
	${OBJECTDIR}/src/StringBuilder.o \
	${OBJECTDIR}/src/MD5Calculator.o \
	${OBJECTDIR}/src/AbstractListAssembler.o \
	${OBJECTDIR}/src/ManagedMap.o \
	${OBJECTDIR}/src/Codec.o \
	${OBJECTDIR}/src/ManagedVector.o \
	${OBJECTDIR}/src/NamedValue.o \
	${OBJECTDIR}/src/util.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=gnu++0x -fomit-frame-pointer -fPIC -pthread -Wall -Wno-parentheses -Wno-switch -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=implicit-function-declaration -ansi
CXXFLAGS=-std=gnu++0x -fomit-frame-pointer -fPIC -pthread -Wall -Wno-parentheses -Wno-switch -Wdisabled-optimization -Wpointer-arith -Wredundant-decls -Wwrite-strings -Wtype-limits -Wundef -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -Werror=implicit-function-declaration -ansi

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a

${OBJECTDIR}/src/JSonWriter.o: src/JSonWriter.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JSonWriter.o src/JSonWriter.cc

${OBJECTDIR}/src/StringBuilder.o: src/StringBuilder.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StringBuilder.o src/StringBuilder.cc

${OBJECTDIR}/src/MD5Calculator.o: src/MD5Calculator.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MD5Calculator.o src/MD5Calculator.cc

${OBJECTDIR}/src/AbstractListAssembler.o: src/AbstractListAssembler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractListAssembler.o src/AbstractListAssembler.cc

${OBJECTDIR}/src/ManagedMap.o: src/ManagedMap.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ManagedMap.o src/ManagedMap.cc

${OBJECTDIR}/src/Codec.o: src/Codec.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Codec.o src/Codec.cc

${OBJECTDIR}/src/ManagedVector.o: src/ManagedVector.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ManagedVector.o src/ManagedVector.cc

${OBJECTDIR}/src/NamedValue.o: src/NamedValue.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/NamedValue.o src/NamedValue.cc

${OBJECTDIR}/src/util.o: src/util.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/util.o src/util.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libutil.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

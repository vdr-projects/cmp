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
	${OBJECTDIR}/src/TimeMs.o \
	${OBJECTDIR}/src/StringList.o \
	${OBJECTDIR}/src/Thread.o \
	${OBJECTDIR}/src/String.o \
	${OBJECTDIR}/src/i18n.o \
	${OBJECTDIR}/src/Logging.o \
	${OBJECTDIR}/src/ReadDir.o \
	${OBJECTDIR}/src/CondWait.o \
	${OBJECTDIR}/src/FileNameList.o \
	${OBJECTDIR}/src/Mutex.o \
	${OBJECTDIR}/src/CharsetConv.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a

${OBJECTDIR}/src/TimeMs.o: src/TimeMs.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TimeMs.o src/TimeMs.cc

${OBJECTDIR}/src/StringList.o: src/StringList.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StringList.o src/StringList.cc

${OBJECTDIR}/src/Thread.o: src/Thread.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Thread.o src/Thread.cc

${OBJECTDIR}/src/String.o: src/String.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/String.o src/String.cc

${OBJECTDIR}/src/i18n.o: src/i18n.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/i18n.o src/i18n.cc

${OBJECTDIR}/src/Logging.o: src/Logging.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Logging.o src/Logging.cc

${OBJECTDIR}/src/ReadDir.o: src/ReadDir.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ReadDir.o src/ReadDir.cc

${OBJECTDIR}/src/CondWait.o: src/CondWait.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CondWait.o src/CondWait.cc

${OBJECTDIR}/src/FileNameList.o: src/FileNameList.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileNameList.o src/FileNameList.cc

${OBJECTDIR}/src/Mutex.o: src/Mutex.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Mutex.o src/Mutex.cc

${OBJECTDIR}/src/CharsetConv.o: src/CharsetConv.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLOCDIR=/usr/share/locale -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I/usr/include/freetype2 -I/usr/include/fribidi -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CharsetConv.o src/CharsetConv.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libvdr.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

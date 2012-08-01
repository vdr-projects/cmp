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
	${OBJECTDIR}/src/JSonListAssembler.o \
	${OBJECTDIR}/src/MediaServerConfig.o \
	${OBJECTDIR}/src/CommandHandler.o \
	${OBJECTDIR}/src/HTMLListAssembler.o \
	${OBJECTDIR}/src/AbstractMediaRequestHandler.o \
	${OBJECTDIR}/src/HTTPMediaResponse.o \
	${OBJECTDIR}/src/MediaListHandler.o \
	${OBJECTDIR}/src/MediaFileHandler.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a

${OBJECTDIR}/src/JSonListAssembler.o: nbproject/Makefile-${CND_CONF}.mk src/JSonListAssembler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JSonListAssembler.o src/JSonListAssembler.cc

${OBJECTDIR}/src/MediaServerConfig.o: nbproject/Makefile-${CND_CONF}.mk src/MediaServerConfig.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaServerConfig.o src/MediaServerConfig.cc

${OBJECTDIR}/src/CommandHandler.o: nbproject/Makefile-${CND_CONF}.mk src/CommandHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CommandHandler.o src/CommandHandler.cc

${OBJECTDIR}/src/HTMLListAssembler.o: nbproject/Makefile-${CND_CONF}.mk src/HTMLListAssembler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTMLListAssembler.o src/HTMLListAssembler.cc

${OBJECTDIR}/src/AbstractMediaRequestHandler.o: nbproject/Makefile-${CND_CONF}.mk src/AbstractMediaRequestHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractMediaRequestHandler.o src/AbstractMediaRequestHandler.cc

${OBJECTDIR}/src/HTTPMediaResponse.o: nbproject/Makefile-${CND_CONF}.mk src/HTTPMediaResponse.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPMediaResponse.o src/HTTPMediaResponse.cc

${OBJECTDIR}/src/MediaListHandler.o: nbproject/Makefile-${CND_CONF}.mk src/MediaListHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaListHandler.o src/MediaListHandler.cc

${OBJECTDIR}/src/MediaFileHandler.o: nbproject/Makefile-${CND_CONF}.mk src/MediaFileHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -D_GNU_SOURCE=1 -D_REENTRANT -Iinclude -I../../libs/mediaScan/include -I../../libs/networking/include -I../../libs/IO/include -I../../libs/util/include -I../../libs/vdr/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaFileHandler.o src/MediaFileHandler.cc

# Subprojects
.build-subprojects:
	cd ../../libs/vdr && ${MAKE}  -f Makefile CONF=Debug
	cd ../../libs/util && ${MAKE}  -f Makefile CONF=Debug
	cd ../../libs/networking && ${MAKE}  -f Makefile CONF=Debug
	cd ../../libs/IO && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserverlib.a

# Subprojects
.clean-subprojects:
	cd ../../libs/vdr && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../libs/util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../libs/networking && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../libs/IO && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

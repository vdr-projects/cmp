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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

${OBJECTDIR}/src/Picture.o: nbproject/Makefile-${CND_CONF}.mk src/Picture.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Picture.o src/Picture.cc

${OBJECTDIR}/src/Audio.o: nbproject/Makefile-${CND_CONF}.mk src/Audio.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Audio.o src/Audio.cc

${OBJECTDIR}/src/DVDImage.o: nbproject/Makefile-${CND_CONF}.mk src/DVDImage.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DVDImage.o src/DVDImage.cc

${OBJECTDIR}/src/VdrRecording.o: nbproject/Makefile-${CND_CONF}.mk src/VdrRecording.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/VdrRecording.o src/VdrRecording.cc

${OBJECTDIR}/src/MediaFactory.o: nbproject/Makefile-${CND_CONF}.mk src/MediaFactory.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaFactory.o src/MediaFactory.cc

${OBJECTDIR}/src/LegacyVdrRecording.o: nbproject/Makefile-${CND_CONF}.mk src/LegacyVdrRecording.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/LegacyVdrRecording.o src/LegacyVdrRecording.cc

${OBJECTDIR}/src/MediainfoReader.o: nbproject/Makefile-${CND_CONF}.mk src/MediainfoReader.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediainfoReader.o src/MediainfoReader.cc

${OBJECTDIR}/src/FSMediaScanner.o: nbproject/Makefile-${CND_CONF}.mk src/FSMediaScanner.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FSMediaScanner.o src/FSMediaScanner.cc

${OBJECTDIR}/src/AbstractMultiFileMovie.o: nbproject/Makefile-${CND_CONF}.mk src/AbstractMultiFileMovie.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractMultiFileMovie.o src/AbstractMultiFileMovie.cc

${OBJECTDIR}/src/AbstractMedia.o: nbproject/Makefile-${CND_CONF}.mk src/AbstractMedia.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractMedia.o src/AbstractMedia.cc

${OBJECTDIR}/src/Movie.o: nbproject/Makefile-${CND_CONF}.mk src/Movie.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Movie.o src/Movie.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libmediascan.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

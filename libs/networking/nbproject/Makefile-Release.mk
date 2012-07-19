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
	${OBJECTDIR}/src/HTTPRequest.o \
	${OBJECTDIR}/src/ServerSocket.o \
	${OBJECTDIR}/src/HTTPAuthorizationRequest.o \
	${OBJECTDIR}/src/Url.o \
	${OBJECTDIR}/src/Principal.o \
	${OBJECTDIR}/src/Authorization.o \
	${OBJECTDIR}/src/ServerConfig.o \
	${OBJECTDIR}/src/HTTPServer.o \
	${OBJECTDIR}/src/ConnectionPoint.o \
	${OBJECTDIR}/src/HTTPResponse.o \
	${OBJECTDIR}/src/ConnectionHandler.o \
	${OBJECTDIR}/src/Credentials.o \
	${OBJECTDIR}/src/HTTPRequestHandler.o \
	${OBJECTDIR}/src/HTTPMessage.o \
	${OBJECTDIR}/src/HTTPFileResponse.o \
	${OBJECTDIR}/src/HTTPParser.o \
	${OBJECTDIR}/src/ClientSocket.o \
	${OBJECTDIR}/src/AbstractSocket.o \
	${OBJECTDIR}/src/HTTPStatus.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a

${OBJECTDIR}/src/HTTPRequest.o: src/HTTPRequest.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPRequest.o src/HTTPRequest.cc

${OBJECTDIR}/src/ServerSocket.o: src/ServerSocket.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ServerSocket.o src/ServerSocket.cc

${OBJECTDIR}/src/HTTPAuthorizationRequest.o: src/HTTPAuthorizationRequest.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPAuthorizationRequest.o src/HTTPAuthorizationRequest.cc

${OBJECTDIR}/src/Url.o: src/Url.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Url.o src/Url.cc

${OBJECTDIR}/src/Principal.o: src/Principal.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Principal.o src/Principal.cc

${OBJECTDIR}/src/Authorization.o: src/Authorization.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Authorization.o src/Authorization.cc

${OBJECTDIR}/src/ServerConfig.o: src/ServerConfig.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ServerConfig.o src/ServerConfig.cc

${OBJECTDIR}/src/HTTPServer.o: src/HTTPServer.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPServer.o src/HTTPServer.cc

${OBJECTDIR}/src/ConnectionPoint.o: src/ConnectionPoint.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionPoint.o src/ConnectionPoint.cc

${OBJECTDIR}/src/HTTPResponse.o: src/HTTPResponse.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPResponse.o src/HTTPResponse.cc

${OBJECTDIR}/src/ConnectionHandler.o: src/ConnectionHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ConnectionHandler.o src/ConnectionHandler.cc

${OBJECTDIR}/src/Credentials.o: src/Credentials.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Credentials.o src/Credentials.cc

${OBJECTDIR}/src/HTTPRequestHandler.o: src/HTTPRequestHandler.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPRequestHandler.o src/HTTPRequestHandler.cc

${OBJECTDIR}/src/HTTPMessage.o: src/HTTPMessage.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPMessage.o src/HTTPMessage.cc

${OBJECTDIR}/src/HTTPFileResponse.o: src/HTTPFileResponse.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPFileResponse.o src/HTTPFileResponse.cc

${OBJECTDIR}/src/HTTPParser.o: src/HTTPParser.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPParser.o src/HTTPParser.cc

${OBJECTDIR}/src/ClientSocket.o: src/ClientSocket.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ClientSocket.o src/ClientSocket.cc

${OBJECTDIR}/src/AbstractSocket.o: src/AbstractSocket.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AbstractSocket.o src/AbstractSocket.cc

${OBJECTDIR}/src/HTTPStatus.o: src/HTTPStatus.cc 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPStatus.o src/HTTPStatus.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnetworking.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

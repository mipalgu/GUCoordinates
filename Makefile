#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

.include "../../mk/c++17.mk"
#CXXSTDFL=-std=c++17

ALL_TARGETS=test robot-local

C_SRCS!=ls *.c
CC_SRCS!=ls *.cc
ALL_HDRS!=ls *.h
SPECIFIC_LIBS+=-lm
SPECIFIC_LIBS+=-lguunits
SPECIFIC_LIBS+=-lgusimplewhiteboard
LOCAL=_LOCAL

${MODULE_BASE}_HDRS=${ALL_HDRS}
PKGCONFIG_NAME=gucoordinates
PKGCONFIG_VERSION=1.0
PKGCONFIG_DESCRIPTION=Utilities for converting between coordinate systems.

#WFLAGS=-Weverything wn-warning-option ${WERROR}
WFLAGS=-Wall -Weverything -Wno-unknown-pragmas -Wno-unknown-warning-option -Werror
CPP03_EXTRA_WFLAGS=-Wno-c++98-compat -Wc++98-compat-extra-semi
CPP11_EXTRA_WFLAGS=-Wno-c++98-compat -Wc++98-compat-extra-semi
CPP14_EXTRA_WFLAGS=-Wno-c++98-compat -Wc++98-compat-extra-semi
CPP17_EXTRA_WFLAGS=-Wno-c++98-compat -Wc++98-compat-extra-semi

all:	all-real

.ifdef IGNORE_TESTS

test:

.else

host-local:
	$Ebmake host-local IGNORE_TESTS=yes

robot-local:
	$Ebmake robot-local IGNORE_TESTS=yes

upload-robot:
	$Ebmake upload-robot IGNORE_TESTS=yes

test: ctest cpptest

ctest:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C Implementation."
	$Ecd ${SRCDIR}/ctests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./ctests/build.host/ctests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp98test:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C++ Implementation with C++98 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp03test:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C++ Implementation with C++03 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=03 EXTRA_WFLAGS="${CPP03_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp11test:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C++ Implementation with C++11 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=11 EXTRA_WFLAGS="${CPP11_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp14test:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C++ Implementation with C++14 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=14 EXTRA_WFLAGS="${CPP14_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp17test:
.ifndef TARGET
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes
	${SAY} "Testing C++ Implementation with C++17 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=17 EXTRA_WFLAGS="${CPP17_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpptest: cpp98test cpp03test cpp11test cpp14test cpp17test
.endif

.ifdef TESTING
HOST_LOCAL_OUTFLAGS=${HOST_LOCAL_SOFLAGS} ${COMMON_OFLAGS}
.endif

.include "../../mk/mipal.mk"
# vim:ft=make
#

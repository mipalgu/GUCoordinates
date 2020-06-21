#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

ALL_TARGETS=test robot-local

C_SRCS!=ls *.c
CC_SRCS!=ls *.cc
ALL_HDRS!=ls *.h
SPECIFIC_LIBS=-lguunits
LOCAL=_LOCAL

.include "../../mk/c++11.mk"

${MODULE_BASE}_HDRS=${ALL_HDRS}
PKGCONFIG_NAME=gucoordinates
PKGCONFIG_VERSION=1.0
PKGCONFIG_DESCRIPTION=Utilities for converting between coordinate systems.

all:	all-real

.ifndef IGNORE_TESTS

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
	$Ecd ${SRCDIR}/ctests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./ctests/build.host/ctests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp98test:
.ifndef TARGET
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp03test:
.ifndef TARGET
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=03 BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp11test:
.ifndef TARGET
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=11 BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp14test:
.ifndef TARGET
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=14 BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpp17test:
.ifndef TARGET
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=17 BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests || cd ${SRCDIR} && env ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes
.endif

cpptest: cpp98test cpp03test cpp11test cpp14test cpp17test
.endif

.ifdef TESTING
HOST_LOCAL_OUTFLAGS=${HOST_LOCAL_SOFLAGS} ${COMMON_OFLAGS}
.endif

.include "../../mk/mipal.mk"
# vim:ft=make
#

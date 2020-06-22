#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

.include "../../mk/c++17.mk"

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
CPP03_EXTRA_WFLAGS=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wc++98-compat-extra-semi
CPP11_EXTRA_WFLAGS=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wc++98-compat-extra-semi
CPP14_EXTRA_WFLAGS=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wc++98-compat-extra-semi
CPP17_EXTRA_WFLAGS=-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wc++98-compat-extra-semi

.ifdef TESTING
CODE_COVERAGE=yes
SPECIFIC_CPPFLAGS+=-fprofile-arcs -ftest-coverage
SPECIFIC_LDFLAGS+=--coverage
.endif

LCOV!=which lcov &2>/dev/null
GENHTML!=which genhtml &2>/dev/null

all:	all-real

coverage:
.if empty(LCOV)
	${SAY} "You must install lcov in order to generate a code coverage report."
.endif
.if empty(GENHTML)
	${SAY} "You must install genhtml in order to generate a code coverage report."
.endif
.if !empty(LCOV) && !empty(GENHTML)
	cp ${SRCDIR}/ctests/build.host/*.gc* build.host-local/ || true 
	cp ${SRCDIR}/tests/build.host/*.gc* build.host-local/ || true
	cd build.host-local && lcov --directory . --base-directory . --gcov-tool gcov --capture -o cov.info && genhtml cov.info -o coverage || cd ${SRCDIR}
.endif

.ifdef IGNORE_TESTS

test:

.else

host-local:
	$Ebmake host-local IGNORE_TESTS=yes

robot-local:
	$Ebmake robot-local IGNORE_TESTS=yes

upload-robot:
	$Ebmake upload-robot IGNORE_TESTS=yes

test: clean ctest cpptest

build-lib:
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes


ctest: build-lib
.ifndef TARGET
	${SAY} "Testing C Implementation."
	$Ecd ${SRCDIR}/ctests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./ctests/build.host/ctests
.endif

cpp98test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++98 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests
.endif

cpp03test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++03 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=03 EXTRA_WFLAGS="${CPP03_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests
.endif

cpp11test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++11 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=11 EXTRA_WFLAGS="${CPP11_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests
.endif

cpp14test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++14 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=14 EXTRA_WFLAGS="${CPP14_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests
.endif

cpp17test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++17 Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=17 EXTRA_WFLAGS="${CPP17_EXTRA_WFLAGS}" BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host/tests
.endif

cpptest: cpp98test cpp03test cpp11test cpp14test cpp17test
.endif

.ifdef TESTING
HOST_LOCAL_OUTFLAGS=${HOST_LOCAL_SOFLAGS} ${COMMON_OFLAGS}
.endif

.include "../../mk/mipal.mk"
# vim:ft=make
#

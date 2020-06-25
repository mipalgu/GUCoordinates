#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

STDS=98 03 11 14 17
STD?=17

.ifdef STD
.  if ${STD} == 03 || ${STD} == 98
CXXSTDFL=-std=c++${STD}
.  else
.    include "../../mk/c++${STD}.mk"
.  endif
.else
CXXSTDFL=-std=c++98
.endif

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

all:	all-real

.ifndef COVERAGE
generate-coverage-report:
	${MAKE} generate-coverage-report COVERAGE=yes

c-coverage:
	${MAKE} c-coverage COVERAGE=yes
.else
CODE_COVERAGE=yes
SPECIFIC_CPPFLAGS+=-fprofile-arcs -ftest-coverage
SPECIFIC_LDFLAGS+=--coverage

LCOV!=which lcov &2>/dev/null
GENHTML!=which genhtml &2>/dev/null

generate-coverage-report:
.if empty(LCOV)
	${SAY} "You must install lcov in order to generate a code coverage report."
.endif
.if empty(GENHTML)
	${SAY} "You must install genhtml in order to generate a code coverage report."
.endif
.if !empty(LCOV) && !empty(GENHTML)
	rm -rf ${COVERAGE_BUILD_DIR}
	mkdir -p ${COVERAGE_BUILD_DIR}
	cp ${TEST_BUILD_DIR}/*.gc* ${COVERAGE_BUILD_DIR}/ || true 
	cp build.host-local/*.gc* ${COVERAGE_BUILD_DIR}/ || true
	cd ${COVERAGE_BUILD_DIR} && lcov --directory . --base-directory ${TEST_BUILD_DIR} --gcov-tool gcov --capture -o cov.info && genhtml --title "${COVERAGE_TITLE}" cov.info -o coverage || cd ${SRCDIR}
.endif


c-coverage:
	bmake generate-coverage-report TEST_BUILD_DIR="${SRCDIR}/ctests/build.host" COVERAGE_BUILD_DIR="coverage/c" COVERAGE_TITLE="C Tests Coverage"
.endif

cpp-coverage:
.for std in ${STDS}
	bmake single-cpp-coverage STD=${std}
.endfor

.ifdef STD
single-cpp-coverage:
	bmake generate-coverage-report TEST_BUILD_DIR="${SRCDIR}/tests/build.host-${STD}" COVERAGE_BUILD_DIR="coverage/${STD}" COVERAGE_TITLE="C++${STD} Tests Coverage"
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

coverage-test:
	$Ebmake test COVERAGE=yes

.ifdef COVERAGE
build-lib: clean
.else
build-lib:
.endif
	$Eenv ${MAKE} host-local MAKEFLAGS= IGNORE_TESTS=yes TESTING=yes

run-cpp-test: build-lib
.ifndef TARGET
	${SAY} "Testing C++ Implementation with C++${STD} Standard."
	$Ecd ${SRCDIR}/tests && ${MAKE} build-test STD=${STD} EXTRA_WFLAGS="${CPP${STD}_EXTRA_WFLAGS}" BUILDDIR=build.host-${STD} LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./tests/build.host-${STD}/tests
.endif

ctest: build-lib
.ifndef TARGET
	${SAY} "Testing C Implementation."
	$Ecd ${SRCDIR}/ctests && ${MAKE} build-test BUILDDIR=build.host LOCAL= MAKEFLAGS= SDIR=${SRCDIR} TESTLIBDIR=${SRCDIR}/build.host-local && cd ${SRCDIR} && ./ctests/build.host/ctests
.ifdef COVERAGE
	$Ebmake c-coverage
.endif
.endif

coverage-ctest:
	$Ebmake ctest COVERAGE=yes

cpptest: ${STDS:=cpp%test}

coverage-cpptest:
	$Ebmake cpptest COVERAGE=yes

.for std in ${STDS}
cpp${std}test: build-lib
	$E${MAKE} run-cpp-test STD=${std}
.ifdef COVERAGE
	$E${MAKE} single-cpp-coverage STD=${std}
.endif

cpp${std}coverage:
	$E${MAKE} cpp${std}test COVERAGE=yes
.endfor

.endif

.ifdef TESTING
HOST_LOCAL_OUTFLAGS=${HOST_LOCAL_SOFLAGS} ${COMMON_OFLAGS}
.endif

.include "../../mk/mipal.mk"
# vim:ft=make
#

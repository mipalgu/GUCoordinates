ALL_TARGETS=build-test

SDIR?=.

HDRS!=ls *.h 2>/dev/null || :
C_SRCS!=ls *.c 2>/dev/null || :
CC_SRCS!=ls *.cc 2>/dev/null || :
CPP_SRCS!=ls *.cpp 2>/dev/null || :
CXXFLAGS+=-I${SDIR} -I../../../../Common -I../../../gusimplewhiteboard
TESTLIBDIR?=${SDIR}/../build.host-local
SPECIFIC_LIBS=-L${TESTLIBDIR} -lgucoordinates -L/usr/local/lib -lgtest -lgtest_main -lguunits -rpath ${TESTLIBDIR}
WFLAGS=

all:	all-real

build-test: clean host
	echo "DISABLE_CPP11: ${DISABLE_CPP11}, USE_CXX11: ${USE_CXX11}"

test:

.ifndef DISABLE_CPP11
.include "../../../mk/c++11.mk"
.else
CXXSTDFL=
.endif

.include "../../../mk/mipal.mk"

LDFLAGS=

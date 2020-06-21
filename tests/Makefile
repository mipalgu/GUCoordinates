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

test:

.ifdef STD
.if ${STD} == 03
CXXSTDFL=-std=c++03
.else
.include "../../../mk/c++${STD}.mk"
.endif
.else
CXXSTDFL=-std=c++98
.endif

.include "../../../mk/mipal.mk"

LDFLAGS=

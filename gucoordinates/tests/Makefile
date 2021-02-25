WFLAGS=-Wall -Weverything -Wno-unknown-pragmas -Wno-unknown-warning-option -Wno-global-constructors -Werror -Wno-padded -Wno-weak-vtables -Wno-c99-extensions -Wno-variadic-macros -Wno-used-but-marked-unused ${EXTRA_WFLAGS} -Wno-poison-system-directories -Wno-suggest-override -Wno-suggest-destructor-override
.ifdef CPP_STD
.  if ${CPP_STD} == 03 || ${CPP_STD} == 98
CXXCPP_STDFL=-std=c++${CPP_STD}
.  else
.    include "../../../../mk/c++${CPP_STD}.mk"
.  endif
.else
CXXCPP_STDFL=-std=c++98
.endif

ALL_TARGETS=build-test

SDIR?=.

HDRS!=ls *.h 2>/dev/null || :
C_SRCS!=ls *.c 2>/dev/null || :
CC_SRCS!=ls *.cc 2>/dev/null || :
CPP_SRCS!=ls *.cpp 2>/dev/null || :
CXXFLAGS+=-I${SDIR} -I../../../../../Common -I../../../../gusimplewhiteboard
TESTLIBDIR?=${SDIR}/../build.host-local
SPECIFIC_LIBS=-L${TESTLIBDIR} -lgucoordinates -L/usr/local/lib -lgtest -lgtest_main -lguunits -rpath ${TESTLIBDIR} --coverage

CODE_COVERAGE=yes

all:	all-real

build-test: clean-build-dir host

test:

clean-build-dir:
	rm -rf ${BUILDDIR}

.include "../../../../mk/mipal.mk"

LDFLAGS=

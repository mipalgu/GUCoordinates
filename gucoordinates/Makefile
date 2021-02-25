#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

ALL_TARGETS=test host-local atom-local atom1-local geode-local xc doc

C_SRCS!=ls *.c
CC_SRCS!=ls *.cc
ALL_HDRS!=ls *.h *.hpp
DOC_HDRS=${ALL_HDRS}
SPECIFIC_LIBS+=-lm
SPECIFIC_LIBS+=-lguunits
LOCAL=_LOCAL

${MODULE_BASE}_HDRS=${ALL_HDRS}
PKGCONFIG_NAME=gucoordinates
PKGCONFIG_VERSION=1.0
PKGCONFIG_DESCRIPTION=Utilities for converting between coordinate systems.



.include "../../../mk/testdir.mk"
.include "../../../mk/mipal.mk"
# vim:ft=make
#


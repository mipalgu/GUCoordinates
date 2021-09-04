#
#	$Id$
#
# Makefile for pre- and cross-compiling .machine files
#
ALL_TARGETS=show-all-dependencies
NO_DEFAULT_DEPENDENCIES_TARGETS=yes

CMAKE_SUBDIR_NAMES?=gucoordinates
SUBDIR_NAMES?=${CMAKE_SUBDIR_NAMES} swift_GUCoordinates

.include "../../mk/subdir.mk"
.include "../../mk/mipal.mk"	# comes last!


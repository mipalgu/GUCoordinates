#
#	$Id$
#
# Makefile for pre- and cross-compiling .machine files
#
ALL_TARGETS=show-all-dependencies
NO_DEFAULT_DEPENDENCIES_TARGETS=yes

SUBDIR_NAMES?=gucoordinates swift_GUCoordinates

.include "../../mk/subdir.mk"
.include "../../mk/mipal.mk"	# comes last!


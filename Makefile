#
#	$Id$
#
# Makefile for pre- and cross-compiling .machine files
#
ALL_TARGETS=show-all-dependencies
NO_DEFAULT_DEPENDENCIES_TARGETS=yes

SRCDIR!=pwd

#DIRS!=find ./ -type d -mindepth 1 -maxdepth 1 -exec basename {} \;
#hack to avoid SwiftMachines dir for now.
DIRS?=gucoordinates swift_GUCoordinates

.ifndef AM_I_JENKINS
SUBDIRS=
. for d in ${DIRS}
.  if exists(${SRCDIR}/$d)
    SUBDIRS+= ${SRCDIR}/$d
.  endif
. endfor
.endif

.for dir in ${SUBDIRS}
INC_DIRS+= -I ${dir}
.endfor

.include "../../mk/subdir.mk"	# comes last!

.include "../../mk/mipal.mk"	# comes last!


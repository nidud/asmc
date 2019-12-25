ifndef __G_VERSION_H__
__G_VERSION_H__ equ 1

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

externdef glib_major_version:guint
externdef glib_minor_version:guint
externdef glib_micro_version:guint
externdef glib_interface_age:guint
externdef glib_binary_age:guint

glib_check_version proto __cdecl \
	required_major: guint,
	required_minor: guint,
	required_micro: guint


GLIB_CHECK_VERSION macro major,minor,micro
	exitm<(GLIB_MAJOR_VERSION GT (major) OR \
	      (GLIB_MAJOR_VERSION EQ (major) AND GLIB_MINOR_VERSION GT (minor)) OR \
	      (GLIB_MAJOR_VERSION EQ (major) AND GLIB_MINOR_VERSION EQ (minor) AND \
	       GLIB_MICRO_VERSION GE (micro)))
	endm
endif

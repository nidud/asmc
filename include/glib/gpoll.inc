ifndef __G_POLL_H__
__G_POLL_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (__G_MAIN_H__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glibconfig.inc
include glib/gtypes.inc

CALLBACKC(GPollFunc, :ptr GPollFD, :guint, :gint)

GPollFD			STRUC
if defined (G_OS_WIN32) AND GLIB_SIZEOF_VOID_P EQ 8
ifndef __GTK_DOC_IGNORE__
fd			gint64 ?
endif
else
fd			gint ?
endif
events			gushort ?
revents			gushort ?
GPollFD			ENDS

;gint
g_poll proto __cdecl \
		   fds: ptr GPollFD,
		  nfds: guint,
	       timeout: gint


endif

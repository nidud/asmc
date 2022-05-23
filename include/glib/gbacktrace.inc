ifndef __G_BACKTRACE_H__
define __G_BACKTRACE_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
ifdef __sun__
include sys/select.inc
endif
include signal.inc

g_on_error_query proto __cdecl \
              prg_name: ptr gchar

g_on_error_stack_trace proto __cdecl \
              prg_name: ptr gchar

endif

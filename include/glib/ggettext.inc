ifndef __G_GETTEXT_H__
define __G_GETTEXT_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc

g_strip_context proto __cdecl :ptr, :ptr
g_dgettext proto __cdecl :ptr, :ptr
g_dcgettext proto __cdecl :ptr, :ptr, :gint
g_dngettext proto __cdecl :ptr, :ptr, :ptr, :gulong
g_dpgettext proto __cdecl :ptr, :ptr, :gsize
g_dpgettext2 proto __cdecl :ptr, :ptr, :ptr

endif

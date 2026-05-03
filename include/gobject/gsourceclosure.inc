ifndef __G_SOURCECLOSURE_H__
define __G_SOURCECLOSURE_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gclosure.inc
include gobject/glib-types.inc

g_source_set_closure proto :ptr, :ptr
g_source_set_dummy_callback proto :ptr

endif

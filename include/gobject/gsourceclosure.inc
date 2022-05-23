ifndef __G_SOURCECLOSURE_H__
define __G_SOURCECLOSURE_H__
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gclosure.inc
include gobject/glib-types.inc

;void
g_source_set_closure proto __cdecl \
                source: ptr GSource,
               closure: ptr GClosure


;void
g_source_set_dummy_callback proto __cdecl \
                source: ptr GSource

endif

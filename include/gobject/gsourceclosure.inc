ifndef __G_SOURCECLOSURE_H__
__G_SOURCECLOSURE_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gclosure.inc
include gobject/glib-types.inc

G_BEGIN_DECLS

;void
g_source_set_closure proto __cdecl \
                source: ptr GSource,
               closure: ptr GClosure


;void
g_source_set_dummy_callback proto __cdecl \
                source: ptr GSource

G_END_DECLS

endif

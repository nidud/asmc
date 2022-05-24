ifndef __G_BINDING_GROUP_H__
define __G_BINDING_GROUP_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc
include gobject/gobject.inc
include gobject/gbinding.inc

G_BINDING_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_BINDING_GROUP, GBindingGroup))>
  endm
G_IS_BINDING_GROUP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_BINDING_GROUP))>
  endm
define G_TYPE_BINDING_GROUP    (g_binding_group_get_type())

;GBindingGroup           typedef _GBindingGroup

g_binding_group_get_type proto
g_binding_group_new proto
g_binding_group_dup_source proto :ptr
g_binding_group_set_source proto :ptr, :gpointer
g_binding_group_bind proto :ptr, :ptr, :gpointer, :ptr, :GBindingFlags
g_binding_group_bind_full proto :ptr, :ptr, :gpointer, :ptr, :GBindingFlags, :GBindingTransformFunc, :GBindingTransformFunc, :gpointer, :GDestroyNotify
g_binding_group_bind_with_closures proto :ptr, :ptr, :gpointer, :ptr, :GBindingFlags, :ptr, :ptr

endif

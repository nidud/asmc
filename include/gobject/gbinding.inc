ifndef __G_BINDING_H__
define __G_BINDING_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc
include gobject/gobject.inc

define G_TYPE_BINDING_FLAGS    <g_binding_flags_get_type ()>
define G_TYPE_BINDING          <g_binding_get_type ()>
G_BINDING macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_BINDING, GBinding))>
  endm
G_IS_BINDING macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_BINDING))>
  endm


CALLBACK(GBindingTransformFunc, :ptr, :ptr, :ptr, :gpointer)

.enum GBindingFlags {
  G_BINDING_DEFAULT        = 0,

  G_BINDING_BIDIRECTIONAL  = 1 shl 0,
  G_BINDING_SYNC_CREATE    = 1 shl 1,
  G_BINDING_INVERT_BOOLEAN = 1 shl 2
}

g_binding_flags_get_type proto
g_binding_get_type proto

g_binding_get_flags proto :ptr
g_binding_get_source proto :ptr
g_binding_dup_source proto :ptr
g_binding_get_target proto :ptr
g_binding_dup_target proto :ptr
g_binding_get_source_property proto :ptr
g_binding_get_target_property proto :ptr
g_binding_unbind proto :ptr

g_object_bind_property proto :gpointer, :ptr, :gpointer, :ptr, :GBindingFlags
g_object_bind_property_full proto :gpointer, :ptr, :gpointer, :ptr, :GBindingFlags, :GBindingTransformFunc, :GBindingTransformFunc, :gpointer, :GDestroyNotify
g_object_bind_property_with_closures proto :gpointer, :ptr, :gpointer, :ptr, :GBindingFlags, :ptr, :ptr

endif

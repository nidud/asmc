ifndef __G_BOXED_H__
define __G_BOXED_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

ifndef __GI_SCANNER__
include gobject/glib-types.inc
endif

G_TYPE_IS_BOXED macro type
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_BOXED)>
  endm

G_VALUE_HOLDS_BOXED macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_BOXED))>
  endm

CALLBACK(GBoxedCopyFunc, :gpointer)
CALLBACK(GBoxedFreeFunc, :gpointer)

g_boxed_copy proto :GType, :gconstpointer
g_boxed_free proto :GType, :gpointer
g_value_set_boxed proto :ptr, :gconstpointer
g_value_set_static_boxed proto :ptr, :gconstpointer
g_value_take_boxed proto :ptr, :gconstpointer
g_value_set_boxed_take_ownership proto :ptr, :gconstpointer
g_value_get_boxed proto :ptr
g_value_dup_boxed proto :ptr

g_boxed_type_register_static proto :ptr, :GBoxedCopyFunc, :GBoxedFreeFunc

define G_TYPE_CLOSURE <g_closure_get_type ()>
define G_TYPE_VALUE <g_value_get_type ()>

g_closure_get_type proto
g_value_get_type proto

endif

ifndef __G_VALUE_H__
define __G_VALUE_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_TYPE_IS_VALUE macro type
  exitm<(g_type_check_is_value_type (type))>
  endm

G_IS_VALUE macro value
  exitm<(G_TYPE_CHECK_VALUE (value))>
  endm

G_VALUE_TYPE macro value
  exitm<(( (value)).g_type)>
  endm

G_VALUE_TYPE_NAME macro value
  exitm<(g_type_name (G_VALUE_TYPE (value)))>
  endm

G_VALUE_HOLDS macro value,type
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), (type)))>
  endm


CALLBACK(GValueTransform, :ptr, :ptr)

_GValue                 struct
g_type                  GType ?
union data;[2]
 v_int                  gint ?
 v_uint                 guint ?
 v_long                 glong ?
 v_ulong                gulong ?
 v_int64                gint64 ?
 v_uint64               guint64 ?
 v_float                gfloat ?
 v_double               gdouble ?
 v_pointer              gpointer ?
ends
_GValue                 ends
GValue                  typedef _GValue

g_value_init proto :ptr, :GType
g_value_copy proto :ptr, :ptr
g_value_reset proto :ptr
g_value_unset proto :ptr
g_value_set_instance proto :ptr, :gpointer
g_value_init_from_instance proto :ptr, :gpointer

g_value_fits_pointer proto :ptr
g_value_peek_pointer proto :ptr

g_value_type_compatible proto :GType, :GType
g_value_type_transformable proto :GType, :GType
g_value_transform proto :ptr, :ptr
g_value_register_transform_func proto :GType, :GType, :GValueTransform

define G_VALUE_NOCOPY_CONTENTS (1 shl 27)
define G_VALUE_INTERNED_STRING (1 shl 28)
define G_VALUE_INIT  <{ 0, { { 0 } } }>

endif

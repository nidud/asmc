ifndef __G_VALUETYPES_H__
define __G_VALUETYPES_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc

G_VALUE_HOLDS_CHAR macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_CHAR))>
  endm

G_VALUE_HOLDS_UCHAR macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_UCHAR))>
  endm

G_VALUE_HOLDS_BOOLEAN macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_BOOLEAN))>
  endm

G_VALUE_HOLDS_INT macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_INT))>
  endm

G_VALUE_HOLDS_UINT macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_UINT))>
  endm

G_VALUE_HOLDS_LONG macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_LONG))>
  endm

G_VALUE_HOLDS_ULONG macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_ULONG))>
  endm

G_VALUE_HOLDS_INT64 macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_INT64))>
  endm

G_VALUE_HOLDS_UINT64 macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_UINT64))>
  endm

G_VALUE_HOLDS_FLOAT macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_FLOAT))>
  endm

G_VALUE_HOLDS_DOUBLE macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_DOUBLE))>
  endm

G_VALUE_HOLDS_STRING macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_STRING))>
  endm

G_VALUE_IS_INTERNED_STRING macro value
  exitm<(G_VALUE_HOLDS_STRING (value) and ((value).data[1].v_uint and G_VALUE_INTERNED_STRING))>
  endm

G_VALUE_HOLDS_POINTER macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_POINTER))>
  endm

define	G_TYPE_GTYPE			 (g_gtype_get_type())

G_VALUE_HOLDS_GTYPE macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_GTYPE))>
  endm

G_VALUE_HOLDS_VARIANT macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_VARIANT))>
  endm

g_value_set_char proto :ptr, :gchar
g_value_get_char proto :ptr
g_value_set_schar proto :ptr, :gint8
g_value_get_schar proto :ptr
g_value_set_uchar proto :ptr, :guchar
g_value_get_uchar proto :ptr
g_value_set_boolean proto :ptr, :gboolean
g_value_get_boolean proto :ptr
g_value_set_int proto :ptr, :gint
g_value_get_int proto :ptr
g_value_set_uint proto :ptr, :guint
g_value_get_uint proto :ptr
g_value_set_long proto :ptr, :glong
g_value_get_long proto :ptr
g_value_set_ulong proto :ptr, :gulong
g_value_get_ulong proto :ptr
g_value_set_int64 proto :ptr, :gint64
g_value_get_int64 proto :ptr
g_value_set_uint64 proto :ptr, :guint64
g_value_get_uint64 proto :ptr
g_value_set_float proto :ptr, :gfloat
g_value_get_float proto :ptr
g_value_set_double proto :ptr, :gdouble
g_value_get_double proto :ptr
g_value_set_string proto :ptr, :ptr
g_value_set_static_string proto :ptr, :ptr
g_value_set_interned_string proto :ptr, :ptr
g_value_get_string proto :ptr
g_value_dup_string proto :ptr
g_value_set_pointer proto :ptr, :gpointer
g_value_get_pointer proto :ptr
g_gtype_get_type proto
g_value_set_gtype proto :ptr, :GType
g_value_get_gtype proto :ptr
g_value_set_variant proto :ptr, :ptr
g_value_take_variant proto :ptr, :ptr
g_value_get_variant proto :ptr
g_value_dup_variant proto :ptr

g_pointer_type_register_static proto :ptr
g_strdup_value_contents proto :ptr

g_value_take_string proto :ptr, :ptr
g_value_set_string_take_ownership proto :ptr, :ptr

gchararray		typedef ptr gchar

endif

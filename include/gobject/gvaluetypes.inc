ifndef __G_VALUETYPES_H__
define __G_VALUETYPES_H__
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
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
G_VALUE_HOLDS_POINTER macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_POINTER))>
	endm
G_TYPE_GTYPE equ <g_gtype_get_type>
G_VALUE_HOLDS_GTYPE macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_GTYPE))>
	endm
G_VALUE_HOLDS_VARIANT macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_VARIANT))>
	endm


;void
g_value_set_char proto __cdecl \
		 value: ptr GValue,
		v_char: gchar

g_value_get_char proto __cdecl \
		 value: ptr GValue

;void
g_value_set_schar proto __cdecl \
		 value: ptr GValue,
		v_char: gint8

;gint8
g_value_get_schar proto __cdecl \
		 value: ptr GValue

;void
g_value_set_uchar proto __cdecl \
		 value: ptr GValue,
	       v_uchar: guchar

;guchar
g_value_get_uchar proto __cdecl \
		 value: ptr GValue

;void
g_value_set_boolean proto __cdecl \
		 value: ptr GValue,
	     v_boolean: gboolean

;gboolean
g_value_get_boolean proto __cdecl \
		 value: ptr GValue

;void
g_value_set_int proto __cdecl \
		 value: ptr GValue,
		 v_int: gint

;gint
g_value_get_int proto __cdecl \
		 value: ptr GValue

;void
g_value_set_uint proto __cdecl \
		 value: ptr GValue,
		v_uint: guint

;guint
g_value_get_uint proto __cdecl \
		 value: ptr GValue

;void
g_value_set_long proto __cdecl \
		 value: ptr GValue,
		v_long: glong

;glong
g_value_get_long proto __cdecl \
		 value: ptr GValue

;void
g_value_set_ulong proto __cdecl \
		 value: ptr GValue,
	       v_ulong: gulong

;gulong
g_value_get_ulong proto __cdecl \
		 value: ptr GValue

;void
g_value_set_int64 proto __cdecl \
		 value: ptr GValue,
	       v_int64: gint64

;gint64
g_value_get_int64 proto __cdecl \
		 value: ptr GValue

;void
g_value_set_uint64 proto __cdecl \
		 value: ptr GValue,
	      v_uint64: guint64

;guint64
g_value_get_uint64 proto __cdecl \
		 value: ptr GValue

;void
g_value_set_float proto __cdecl \
		 value: ptr GValue,
	       v_float: gfloat

;gfloat
g_value_get_float proto __cdecl \
		 value: ptr GValue

;void
g_value_set_double proto __cdecl \
		 value: ptr GValue,
	      v_double: gdouble

;gdouble
g_value_get_double proto __cdecl \
		 value: ptr GValue

;void
g_value_set_string proto __cdecl \
		 value: ptr GValue,
	      v_string: ptr gchar

;void
g_value_set_static_string proto __cdecl \
		 value: ptr GValue,
	      v_string: ptr gchar

;const
g_value_get_string proto __cdecl \
		 value: ptr GValue

;gchar*
g_value_dup_string proto __cdecl \
		 value: ptr GValue

;void
g_value_set_pointer proto __cdecl \
		 value: ptr GValue,
	     v_pointer: gpointer

;gpointer
g_value_get_pointer proto __cdecl \
		 value: ptr GValue

;GType
g_gtype_get_type proto __cdecl
;void
g_value_set_gtype proto __cdecl \
		 value: ptr GValue,
	       v_gtype: GType

;GType
g_value_get_gtype proto __cdecl \
		 value: ptr GValue

;void
g_value_set_variant proto __cdecl \
		 value: ptr GValue,
	       variant: ptr GVariant

;void
g_value_take_variant proto __cdecl \
		 value: ptr GValue,
	       variant: ptr GVariant

;GVariant*
g_value_get_variant proto __cdecl \
		 value: ptr GValue

;GVariant*
g_value_dup_variant proto __cdecl \
		 value: ptr GValue

;GType
g_pointer_type_register_static proto __cdecl \
		  name: ptr gchar
;gchar*
g_strdup_value_contents proto __cdecl \
		 value: ptr GValue

;void
g_value_take_string proto __cdecl \
		 value: ptr GValue,
	      v_string: ptr gchar

;void
g_value_set_string_take_ownership proto __cdecl \
		 value: ptr GValue,
	      v_string: ptr gchar


gchararray typedef ptr gchar

endif

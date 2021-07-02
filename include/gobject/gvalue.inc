ifndef __G_VALUE_H__
__G_VALUE_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
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
	exitm<(((GValue*) (value))- GT g_type)>
	endm
G_VALUE_TYPE_NAME macro value
	exitm<(g_type_name (G_VALUE_TYPE (value)))>
	endm
G_VALUE_HOLDS macro value,type
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), (type)))>
	endm


CALLBACKC(GValueTransform, :ptr GValue, :ptr GValue)

GValue			STRUC
g_type			GType ?
UNION
v_int			gint ?
v_uint			guint ?
v_long			glong ?
v_ulong			gulong ?
v_int64			gint64 ?
v_uint64		guint64 ?
v_float			gfloat ?
v_double		gdouble ?
v_pointer		gpointer ?
ENDS ;data[2]
GValue			ENDS

;GValue*
g_value_init proto __cdecl \
		 value: ptr GValue,
		g_type: GType

;void
g_value_copy proto __cdecl \
	     src_value: ptr GValue,
	    dest_value: ptr GValue

;GValue*
g_value_reset proto __cdecl \
		 value: ptr GValue

;void
g_value_unset proto __cdecl \
		 value: ptr GValue

;void
g_value_set_instance proto __cdecl \
		 value: ptr GValue,
	      instance: gpointer

;void
g_value_init_from_instance proto __cdecl \
		 value: ptr GValue,
	      instance: gpointer

;gboolean
g_value_fits_pointer proto __cdecl \
		 value: ptr GValue

;gpointer
g_value_peek_pointer proto __cdecl \
		 value: ptr GValue

;gboolean
g_value_type_compatible proto __cdecl \
	      src_type: GType,
	     dest_type: GType

;gboolean
g_value_type_transformable proto __cdecl \
	      src_type: GType,
	     dest_type: GType

;gboolean
g_value_transform proto __cdecl \
	     src_value: ptr GValue,
	    dest_value: ptr GValue

;void
g_value_register_transform_func proto __cdecl \
	      src_type: GType,
	     dest_type: GType,
	transform_func: GValueTransform


G_VALUE_NOCOPY_CONTENTS equ (1 SHL 27)
G_VALUE_INIT		equ <{ 0, { { 0 } } }>

endif

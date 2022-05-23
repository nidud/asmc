ifndef __G_ENUMS_H__
__G_ENUMS_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_TYPE_IS_ENUM macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_ENUM)>
	endm
G_ENUM_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_ENUM, GEnumClass))>
	endm
G_IS_ENUM_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_ENUM))>
	endm
G_ENUM_CLASS_TYPE macro class
	exitm<(G_TYPE_FROM_CLASS (class))>
	endm
G_ENUM_CLASS_TYPE_NAME macro class
	exitm<(g_type_name (G_ENUM_CLASS_TYPE (class)))>
	endm


G_TYPE_IS_FLAGS macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_FLAGS)>
	endm
G_FLAGS_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_FLAGS, GFlagsClass))>
	endm
G_IS_FLAGS_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_FLAGS))>
	endm
G_FLAGS_CLASS_TYPE macro class
	exitm<(G_TYPE_FROM_CLASS (class))>
	endm
G_FLAGS_CLASS_TYPE_NAME macro class
	exitm<(g_type_name (G_FLAGS_CLASS_TYPE (class)))>
	endm


G_VALUE_HOLDS_ENUM macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_ENUM))>
	endm
G_VALUE_HOLDS_FLAGS macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_FLAGS))>
	endm

GEnumClass		STRUC
g_type_class		GTypeClass <>
minimum			gint ?
maximum			gint ?
n_values		guint ?
values			ptr_t ?
GEnumClass		ENDS

GFlagsClass		STRUC
g_type_class		GTypeClass <>
mask			guint ?
n_values		guint ?
values			ptr_t ?
GFlagsClass		ENDS

GEnumValue		STRUC
value			gint ?
value_name		ptr_t ?
value_nick		ptr_t ?
GEnumValue		ENDS

GFlagsValue		STRUC
value			guint ?
value_name		ptr_t ?
value_nick		ptr_t ?
GFlagsValue		ENDS

;GEnumValue*
g_enum_get_value proto __cdecl \
	    enum_class: ptr GEnumClass,
		 value: gint

;GEnumValue*
g_enum_get_value_by_name proto __cdecl \
	    enum_class: ptr GEnumClass,
		  name: ptr gchar

;GEnumValue*
g_enum_get_value_by_nick proto __cdecl \
	    enum_class: ptr GEnumClass,
		  nick: ptr gchar

;GFlagsValue*
g_flags_get_first_value proto __cdecl \
	   flags_class: ptr GFlagsClass,
		 value: guint

;GFlagsValue*
g_flags_get_value_by_name proto __cdecl \
	   flags_class: ptr GFlagsClass,
		  name: ptr gchar

;GFlagsValue*
g_flags_get_value_by_nick proto __cdecl \
	   flags_class: ptr GFlagsClass,
		  nick: ptr gchar

;void
g_value_set_enum proto __cdecl \
		 value: ptr GValue,
		v_enum: gint

;gint
g_value_get_enum proto __cdecl \
		 value: ptr GValue

;void
g_value_set_flags proto __cdecl \
		 value: ptr GValue,
	       v_flags: guint

;guint
g_value_get_flags proto __cdecl \
		 value: ptr GValue

;GType
g_enum_register_static proto __cdecl \
		  name: ptr gchar,
   const_static_values: ptr GEnumValue

;GType
g_flags_register_static proto __cdecl \
		  name: ptr gchar,
   const_static_values: ptr GFlagsValue

;void
g_enum_complete_type_info proto __cdecl \
	   g_enum_type: GType,
		  info: ptr GTypeInfo,
	  const_values: ptr GEnumValue

;void
g_flags_complete_type_info proto __cdecl \
	  g_flags_type: GType,
		  info: ptr GTypeInfo,
	  const_values: ptr GFlagsValue


endif

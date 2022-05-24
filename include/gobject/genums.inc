ifndef __G_ENUMS_H__
define __G_ENUMS_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_TYPE_IS_ENUM macro type
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_ENUM)>
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
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_FLAGS)>
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


_GEnumClass             struct
g_type_class            GTypeClass <>
minimum                 gint ?
maximum                 gint ?
n_values                guint ?
values                  ptr GEnumValue ?
_GEnumClass             ends

_GFlagsClass            struct
g_type_class            GTypeClass <>
mask                    guint ?
n_values                guint ?
values                  ptr GFlagsValue ?
_GFlagsClass            ends

_GEnumValue             struct
value                   gint ?
value_name              ptr gchar ?
value_nick              ptr gchar ?
_GEnumValue             ends

_GFlagsValue            struct
value                   guint ?
value_name              ptr gchar ?
value_nick              ptr gchar ?
_GFlagsValue            ends

GEnumClass              typedef _GEnumClass
GFlagsClass             typedef _GFlagsClass
GEnumValue              typedef _GEnumValue
GFlagsValue             typedef _GFlagsValue

g_enum_get_value proto :ptr, :gint
g_enum_get_value_by_name proto :ptr, :ptr
g_enum_get_value_by_nick proto :ptr, :ptr
g_flags_get_first_value proto :ptr, :guint
g_flags_get_value_by_name proto :ptr, :ptr
g_flags_get_value_by_nick proto :ptr, :ptr
g_enum_to_string proto :GType, :gint
g_flags_to_string proto :GType, :guint
g_value_set_enum proto :ptr, :gint
g_value_get_enum proto :ptr
g_value_set_flags proto :ptr, :guint
g_value_get_flags proto :ptr

g_enum_register_static proto :ptr, :ptr
g_flags_register_static proto :ptr, :ptr

g_enum_complete_type_info proto :GType, :ptr, :ptr
g_flags_complete_type_info proto :GType, :ptr, :ptr

endif

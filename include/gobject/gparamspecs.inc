ifndef __G_PARAMSPECS_H__
define __G_PARAMSPECS_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc
include gobject/genums.inc
include gobject/gboxed.inc
include gobject/gobject.inc

define	G_TYPE_PARAM_CHAR		   (g_param_spec_types[0])

G_IS_PARAM_SPEC_CHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_CHAR))>
  endm

G_PARAM_SPEC_CHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_CHAR, GParamSpecChar))>
  endm


define	G_TYPE_PARAM_UCHAR		   (g_param_spec_types[1])

G_IS_PARAM_SPEC_UCHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UCHAR))>
  endm

G_PARAM_SPEC_UCHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UCHAR, GParamSpecUChar))>
  endm


define	G_TYPE_PARAM_BOOLEAN		   (g_param_spec_types[2])

G_IS_PARAM_SPEC_BOOLEAN macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_BOOLEAN))>
  endm

G_PARAM_SPEC_BOOLEAN macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_BOOLEAN, GParamSpecBoolean))>
  endm


define	G_TYPE_PARAM_INT		   (g_param_spec_types[3])

G_IS_PARAM_SPEC_INT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_INT))>
  endm

G_PARAM_SPEC_INT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_INT, GParamSpecInt))>
  endm


define	G_TYPE_PARAM_UINT		   (g_param_spec_types[4])

G_IS_PARAM_SPEC_UINT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UINT))>
  endm

G_PARAM_SPEC_UINT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UINT, GParamSpecUInt))>
  endm


define	G_TYPE_PARAM_LONG		   (g_param_spec_types[5])

G_IS_PARAM_SPEC_LONG macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_LONG))>
  endm

G_PARAM_SPEC_LONG macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_LONG, GParamSpecLong))>
  endm


define	G_TYPE_PARAM_ULONG		   (g_param_spec_types[6])

G_IS_PARAM_SPEC_ULONG macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_ULONG))>
  endm

G_PARAM_SPEC_ULONG macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_ULONG, GParamSpecULong))>
  endm


define	G_TYPE_PARAM_INT64		   (g_param_spec_types[7])

G_IS_PARAM_SPEC_INT64 macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_INT64))>
  endm

G_PARAM_SPEC_INT64 macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_INT64, GParamSpecInt64))>
  endm


define	G_TYPE_PARAM_UINT64		   (g_param_spec_types[8])

G_IS_PARAM_SPEC_UINT64 macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UINT64))>
  endm

G_PARAM_SPEC_UINT64 macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UINT64, GParamSpecUInt64))>
  endm


define	G_TYPE_PARAM_UNICHAR		   (g_param_spec_types[9])

G_PARAM_SPEC_UNICHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UNICHAR, GParamSpecUnichar))>
  endm

G_IS_PARAM_SPEC_UNICHAR macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UNICHAR))>
  endm


define	G_TYPE_PARAM_ENUM		   (g_param_spec_types[10])

G_IS_PARAM_SPEC_ENUM macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_ENUM))>
  endm

G_PARAM_SPEC_ENUM macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_ENUM, GParamSpecEnum))>
  endm


define	G_TYPE_PARAM_FLAGS		   (g_param_spec_types[11])

G_IS_PARAM_SPEC_FLAGS macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_FLAGS))>
  endm

G_PARAM_SPEC_FLAGS macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_FLAGS, GParamSpecFlags))>
  endm


define	G_TYPE_PARAM_FLOAT		   (g_param_spec_types[12])

G_IS_PARAM_SPEC_FLOAT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_FLOAT))>
  endm

G_PARAM_SPEC_FLOAT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_FLOAT, GParamSpecFloat))>
  endm


define	G_TYPE_PARAM_DOUBLE		   (g_param_spec_types[13])

G_IS_PARAM_SPEC_DOUBLE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_DOUBLE))>
  endm

G_PARAM_SPEC_DOUBLE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_DOUBLE, GParamSpecDouble))>
  endm


define	G_TYPE_PARAM_STRING		   (g_param_spec_types[14])

G_IS_PARAM_SPEC_STRING macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_STRING))>
  endm

G_PARAM_SPEC_STRING macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_STRING, GParamSpecString))>
  endm


define	G_TYPE_PARAM_PARAM		   (g_param_spec_types[15])

G_IS_PARAM_SPEC_PARAM macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_PARAM))>
  endm

G_PARAM_SPEC_PARAM macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_PARAM, GParamSpecParam))>
  endm


define	G_TYPE_PARAM_BOXED		   (g_param_spec_types[16])

G_IS_PARAM_SPEC_BOXED macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_BOXED))>
  endm

G_PARAM_SPEC_BOXED macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_BOXED, GParamSpecBoxed))>
  endm


define	G_TYPE_PARAM_POINTER		   (g_param_spec_types[17])

G_IS_PARAM_SPEC_POINTER macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_POINTER))>
  endm

G_PARAM_SPEC_POINTER macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_POINTER, GParamSpecPointer))>
  endm


define	G_TYPE_PARAM_VALUE_ARRAY	   (g_param_spec_types[18]) GLIB_DEPRECATED_MACRO_IN_2_32

G_IS_PARAM_SPEC_VALUE_ARRAY macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_VALUE_ARRAY)) GLIB_DEPRECATED_MACRO_IN_2_32>
  endm

G_PARAM_SPEC_VALUE_ARRAY macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_VALUE_ARRAY, GParamSpecValueArray)) GLIB_DEPRECATED_MACRO_IN_2_32>
  endm


define	G_TYPE_PARAM_OBJECT		   (g_param_spec_types[19])

G_IS_PARAM_SPEC_OBJECT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_OBJECT))>
  endm

G_PARAM_SPEC_OBJECT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_OBJECT, GParamSpecObject))>
  endm


define	G_TYPE_PARAM_OVERRIDE		   (g_param_spec_types[20])

G_IS_PARAM_SPEC_OVERRIDE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_OVERRIDE))>
  endm

G_PARAM_SPEC_OVERRIDE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_OVERRIDE, GParamSpecOverride))>
  endm


define	G_TYPE_PARAM_GTYPE		   (g_param_spec_types[21])

G_IS_PARAM_SPEC_GTYPE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_GTYPE))>
  endm

G_PARAM_SPEC_GTYPE macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_GTYPE, GParamSpecGType))>
  endm


define G_TYPE_PARAM_VARIANT		   (g_param_spec_types[22])

G_IS_PARAM_SPEC_VARIANT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_VARIANT))>
  endm

G_PARAM_SPEC_VARIANT macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_VARIANT, GParamSpecVariant))>
  endm

_GParamSpecChar		struct
parent_instance		GParamSpec <>
minimum			gint8 ?
maximum			gint8 ?
default_value		gint8 ?
_GParamSpecChar		ends

_GParamSpecUChar	struct
parent_instance		GParamSpec <>
minimum			guint8 ?
maximum			guint8 ?
default_value		guint8 ?
_GParamSpecUChar	ends

_GParamSpecBoolean	struct
parent_instance		GParamSpec <>
default_value		gboolean ?
_GParamSpecBoolean	ends

_GParamSpecInt		struct
parent_instance		GParamSpec <>
minimum			gint ?
maximum			gint ?
default_value		gint ?
_GParamSpecInt		ends

_GParamSpecUInt		struct
parent_instance		GParamSpec <>
minimum			guint ?
maximum			guint ?
default_value		guint ?
_GParamSpecUInt		ends

_GParamSpecLong		struct
parent_instance		GParamSpec <>
minimum			glong ?
maximum			glong ?
default_value		glong ?
_GParamSpecLong		ends

_GParamSpecULong	struct
parent_instance		GParamSpec <>
minimum			gulong ?
maximum			gulong ?
default_value		gulong ?
_GParamSpecULong	ends

_GParamSpecInt64	struct
parent_instance		GParamSpec <>
minimum			gint64 ?
maximum			gint64 ?
default_value		gint64 ?
_GParamSpecInt64	ends

_GParamSpecUInt64	struct
parent_instance		GParamSpec <>
minimum			guint64 ?
maximum			guint64 ?
default_value		guint64 ?
_GParamSpecUInt64	ends

_GParamSpecUnichar	struct
parent_instance		GParamSpec <>
default_value		gunichar ?
_GParamSpecUnichar	ends

_GParamSpecEnum		struct
parent_instance		GParamSpec <>
enum_class		ptr GEnumClass ?
default_value		gint ?
_GParamSpecEnum		ends

_GParamSpecFlags	struct
parent_instance		GParamSpec <>
flags_class		ptr GFlagsClass ?
default_value		guint ?
_GParamSpecFlags	ends

_GParamSpecFloat	struct
parent_instance		GParamSpec <>
minimum			gfloat ?
maximum			gfloat ?
default_value		gfloat ?
epsilon			gfloat ?
_GParamSpecFloat	ends

_GParamSpecDouble	struct
parent_instance		GParamSpec <>
minimum			gdouble ?
maximum			gdouble ?
default_value		gdouble ?
epsilon			gdouble ?
_GParamSpecDouble	ends

_GParamSpecString	struct
parent_instance		GParamSpec <>
default_value		ptr gchar ?
cset_first		ptr gchar ?
cset_nth		ptr gchar ?
substitutor		gchar ?
RECORD
null_fold_if_empty	guint :	 1 ?
ensure_non_null		guint :	 1 ?
ENDS
_GParamSpecString	ends

_GParamSpecParam	struct
parent_instance		GParamSpec <>
_GParamSpecParam	ends

_GParamSpecBoxed	struct
parent_instance		GParamSpec <>
_GParamSpecBoxed	ends

_GParamSpecPointer	struct
parent_instance		GParamSpec <>
_GParamSpecPointer	ends

_GParamSpecValueArray	struct
parent_instance		GParamSpec <>
element_spec		ptr GParamSpec ?
fixed_n_elements	guint ?
_GParamSpecValueArray	ends

_GParamSpecObject	struct
parent_instance		GParamSpec <>
_GParamSpecObject	ends

_GParamSpecOverride	struct
parent_instance		GParamSpec <>
overridden		ptr GParamSpec ?
_GParamSpecOverride	ends

_GParamSpecGType	struct
parent_instance		GParamSpec <>
is_a_type		GType ?
_GParamSpecGType	ends

_GParamSpecVariant	struct
parent_instance		GParamSpec <>
type			ptr GVariantType ?
default_value		ptr GVariant ?
padding			gpointer 4 dup(?)
_GParamSpecVariant	ends

GParamSpecChar		typedef _GParamSpecChar
GParamSpecUChar		typedef _GParamSpecUChar
GParamSpecBoolean	typedef _GParamSpecBoolean
GParamSpecInt		typedef _GParamSpecInt
GParamSpecUInt		typedef _GParamSpecUInt
GParamSpecLong		typedef _GParamSpecLong
GParamSpecULong		typedef _GParamSpecULong
GParamSpecInt64		typedef _GParamSpecInt64
GParamSpecUInt64	typedef _GParamSpecUInt64
GParamSpecUnichar	typedef _GParamSpecUnichar
GParamSpecEnum		typedef _GParamSpecEnum
GParamSpecFlags		typedef _GParamSpecFlags
GParamSpecFloat		typedef _GParamSpecFloat
GParamSpecDouble	typedef _GParamSpecDouble
GParamSpecString	typedef _GParamSpecString
GParamSpecParam		typedef _GParamSpecParam
GParamSpecBoxed		typedef _GParamSpecBoxed
GParamSpecPointer	typedef _GParamSpecPointer
GParamSpecValueArray	typedef _GParamSpecValueArray
GParamSpecObject	typedef _GParamSpecObject
GParamSpecOverride	typedef _GParamSpecOverride
GParamSpecGType		typedef _GParamSpecGType
GParamSpecVariant	typedef _GParamSpecVariant

g_param_spec_char proto :ptr, :ptr, :ptr, :gint8, :gint8, :gint8, :GParamFlags
g_param_spec_uchar proto :ptr, :ptr, :ptr, :guint8, :guint8, :guint8, :GParamFlags
g_param_spec_boolean proto :ptr, :ptr, :ptr, :gboolean, :GParamFlags
g_param_spec_int proto :ptr, :ptr, :ptr, :gint, :gint, :gint, :GParamFlags
g_param_spec_uint proto :ptr, :ptr, :ptr, :guint, :guint, :guint, :GParamFlags
g_param_spec_long proto :ptr, :ptr, :ptr, :glong, :glong, :glong, :GParamFlags
g_param_spec_ulong proto :ptr, :ptr, :ptr, :gulong, :gulong, :gulong, :GParamFlags
g_param_spec_int64 proto :ptr, :ptr, :ptr, :gint64, :gint64, :gint64, :GParamFlags
g_param_spec_uint64 proto :ptr, :ptr, :ptr, :guint64, :guint64, :guint64, :GParamFlags
g_param_spec_unichar proto :ptr, :ptr, :ptr, :gunichar, :GParamFlags
g_param_spec_enum proto :ptr, :ptr, :ptr, :GType, :gint, :GParamFlags
g_param_spec_flags proto :ptr, :ptr, :ptr, :GType, :guint, :GParamFlags
g_param_spec_float proto :ptr, :ptr, :ptr, :gfloat, :gfloat, :gfloat, :GParamFlags
g_param_spec_double proto :ptr, :ptr, :ptr, :gdouble, :gdouble, :gdouble, :GParamFlags
g_param_spec_string proto :ptr, :ptr, :ptr, :ptr, :GParamFlags
g_param_spec_param proto :ptr, :ptr, :ptr, :GType, :GParamFlags
g_param_spec_boxed proto :ptr, :ptr, :ptr, :GType, :GParamFlags
g_param_spec_pointer proto :ptr, :ptr, :ptr, :GParamFlags
g_param_spec_value_array proto :ptr, :ptr, :ptr, :ptr, :GParamFlags
g_param_spec_object proto :ptr, :ptr, :ptr, :GType, :GParamFlags
g_param_spec_override proto :ptr, :ptr
g_param_spec_gtype proto :ptr, :ptr, :ptr, :GType, :GParamFlags
g_param_spec_variant proto :ptr, :ptr, :ptr, :ptr, :ptr, :GParamFlags

endif

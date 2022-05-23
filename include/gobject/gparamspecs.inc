ifndef __G_PARAMSPECS_H__
__G_PARAMSPECS_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc
include gobject/genums.inc
include gobject/gboxed.inc
include gobject/gobject.inc

G_TYPE_PARAM_CHAR	equ <g_param_spec_types[0]>
G_IS_PARAM_SPEC_CHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_CHAR))>
	endm
G_PARAM_SPEC_CHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_CHAR, GParamSpecChar))>
	endm

G_TYPE_PARAM_UCHAR	equ <g_param_spec_types[1]>
G_IS_PARAM_SPEC_UCHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UCHAR))>
	endm
G_PARAM_SPEC_UCHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UCHAR, GParamSpecUChar))>
	endm

G_TYPE_PARAM_BOOLEAN	equ <g_param_spec_types[2]>
G_IS_PARAM_SPEC_BOOLEAN macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_BOOLEAN))>
	endm
G_PARAM_SPEC_BOOLEAN macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_BOOLEAN, GParamSpecBoolean))>
	endm

G_TYPE_PARAM_INT	equ <g_param_spec_types[3]>
G_IS_PARAM_SPEC_INT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_INT))>
	endm
G_PARAM_SPEC_INT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_INT, GParamSpecInt))>
	endm

G_TYPE_PARAM_UINT	equ <g_param_spec_types[4]>
G_IS_PARAM_SPEC_UINT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UINT))>
	endm
G_PARAM_SPEC_UINT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UINT, GParamSpecUInt))>
	endm

G_TYPE_PARAM_LONG	equ <g_param_spec_types[5]>
G_IS_PARAM_SPEC_LONG macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_LONG))>
	endm
G_PARAM_SPEC_LONG macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_LONG, GParamSpecLong))>
	endm

G_TYPE_PARAM_ULONG	equ <g_param_spec_types[6]>
G_IS_PARAM_SPEC_ULONG macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_ULONG))>
	endm
G_PARAM_SPEC_ULONG macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_ULONG, GParamSpecULong))>
	endm

G_TYPE_PARAM_INT64	equ <g_param_spec_types[7]>
G_IS_PARAM_SPEC_INT64 macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_INT64))>
	endm
G_PARAM_SPEC_INT64 macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_INT64, GParamSpecInt64))>
	endm

G_TYPE_PARAM_UINT64	equ <g_param_spec_types[8]>
G_IS_PARAM_SPEC_UINT64 macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UINT64))>
	endm
G_PARAM_SPEC_UINT64 macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UINT64, GParamSpecUInt64))>
	endm

G_TYPE_PARAM_UNICHAR	equ <g_param_spec_types[9]>
G_PARAM_SPEC_UNICHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_UNICHAR, GParamSpecUnichar))>
	endm
G_IS_PARAM_SPEC_UNICHAR macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_UNICHAR))>
	endm

G_TYPE_PARAM_ENUM	equ <g_param_spec_types[10]>
G_IS_PARAM_SPEC_ENUM macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_ENUM))>
	endm
G_PARAM_SPEC_ENUM macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_ENUM, GParamSpecEnum))>
	endm

G_TYPE_PARAM_FLAGS	equ <g_param_spec_types[11]>
G_IS_PARAM_SPEC_FLAGS macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_FLAGS))>
	endm
G_PARAM_SPEC_FLAGS macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_FLAGS, GParamSpecFlags))>
	endm

G_TYPE_PARAM_FLOAT	equ <g_param_spec_types[12]>
G_IS_PARAM_SPEC_FLOAT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_FLOAT))>
	endm
G_PARAM_SPEC_FLOAT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_FLOAT, GParamSpecFloat))>
	endm

G_TYPE_PARAM_DOUBLE	equ <g_param_spec_types[13]>
G_IS_PARAM_SPEC_DOUBLE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_DOUBLE))>
	endm
G_PARAM_SPEC_DOUBLE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_DOUBLE, GParamSpecDouble))>
	endm

G_TYPE_PARAM_STRING	equ <g_param_spec_types[14]>
G_IS_PARAM_SPEC_STRING macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_STRING))>
	endm
G_PARAM_SPEC_STRING macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_STRING, GParamSpecString))>
	endm

G_TYPE_PARAM_PARAM	equ <g_param_spec_types[15]>
G_IS_PARAM_SPEC_PARAM macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_PARAM))>
	endm
G_PARAM_SPEC_PARAM macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_PARAM, GParamSpecParam))>
	endm

G_TYPE_PARAM_BOXED	equ <g_param_spec_types[16]>
G_IS_PARAM_SPEC_BOXED macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_BOXED))>
	endm
G_PARAM_SPEC_BOXED macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_BOXED, GParamSpecBoxed))>
	endm

G_TYPE_PARAM_POINTER	equ <g_param_spec_types[17]>
G_IS_PARAM_SPEC_POINTER macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_POINTER))>
	endm
G_PARAM_SPEC_POINTER macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_POINTER, GParamSpecPointer))>
	endm

G_TYPE_PARAM_VALUE_ARRAY equ <g_param_spec_types[18]>
G_IS_PARAM_SPEC_VALUE_ARRAY macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_VALUE_ARRAY))>
	endm
G_PARAM_SPEC_VALUE_ARRAY macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_VALUE_ARRAY, GParamSpecValueArray))>
	endm

G_TYPE_PARAM_OBJECT	equ <g_param_spec_types[19]>
G_IS_PARAM_SPEC_OBJECT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_OBJECT))>
	endm
G_PARAM_SPEC_OBJECT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_OBJECT, GParamSpecObject))>
	endm

G_TYPE_PARAM_OVERRIDE	equ <g_param_spec_types[20]>
G_IS_PARAM_SPEC_OVERRIDE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_OVERRIDE))>
	endm
G_PARAM_SPEC_OVERRIDE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_OVERRIDE, GParamSpecOverride))>
	endm

G_TYPE_PARAM_GTYPE	equ <g_param_spec_types[21]>
G_IS_PARAM_SPEC_GTYPE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_GTYPE))>
	endm
G_PARAM_SPEC_GTYPE macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_GTYPE, GParamSpecGType))>
	endm

G_TYPE_PARAM_VARIANT	equ <g_param_spec_types[22]>
G_IS_PARAM_SPEC_VARIANT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM_VARIANT))>
	endm
G_PARAM_SPEC_VARIANT macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM_VARIANT, GParamSpecVariant))>
	endm

GParamSpecChar		STRUC
parent_instance		GParamSpec <>
minimum			gint8 ?
maximum			gint8 ?
default_value		gint8 ?
GParamSpecChar		ENDS

GParamSpecUChar		STRUC
parent_instance		GParamSpec <>
minimum			guint8 ?
maximum			guint8 ?
default_value		guint8 ?
GParamSpecUChar		ENDS

GParamSpecBoolean	STRUC
parent_instance		GParamSpec <>
default_value		gboolean ?
GParamSpecBoolean	ENDS

GParamSpecInt		STRUC
parent_instance		GParamSpec <>
minimum			gint ?
maximum			gint ?
default_value		gint ?
GParamSpecInt		ENDS

GParamSpecUInt		STRUC
parent_instance		GParamSpec <>
minimum			guint ?
maximum			guint ?
default_value		guint ?
GParamSpecUInt		ENDS

GParamSpecLong		STRUC
parent_instance		GParamSpec <>
minimum			glong ?
maximum			glong ?
default_value		glong ?
GParamSpecLong		ENDS

GParamSpecULong		STRUC
parent_instance		GParamSpec <>
minimum			gulong ?
maximum			gulong ?
default_value		gulong ?
GParamSpecULong		ENDS

GParamSpecInt64		STRUC
parent_instance		GParamSpec <>
minimum			gint64 ?
maximum			gint64 ?
default_value		gint64 ?
GParamSpecInt64		ENDS

GParamSpecUInt64	STRUC
parent_instance		GParamSpec <>
minimum			guint64 ?
maximum			guint64 ?
default_value		guint64 ?
GParamSpecUInt64	ENDS

GParamSpecUnichar	STRUC
parent_instance		GParamSpec <>
default_value		gunichar ?
GParamSpecUnichar	ENDS

GParamSpecEnum		STRUC
parent_instance		GParamSpec <>
enum_class		ptr_t ?
default_value		gint ?
GParamSpecEnum		ENDS

GParamSpecFlags		STRUC
parent_instance		GParamSpec <>
flags_class		ptr_t ?
default_value		guint ?
GParamSpecFlags		ENDS

GParamSpecFloat		STRUC
parent_instance		GParamSpec <>
minimum			gfloat ?
maximum			gfloat ?
default_value		gfloat ?
epsilon			gfloat ?
GParamSpecFloat		ENDS

GParamSpecDouble	STRUC
parent_instance		GParamSpec <>
minimum			gdouble ?
maximum			gdouble ?
default_value		gdouble ?
epsilon			gdouble ?
GParamSpecDouble	ENDS

GParamSpecString	STRUC
parent_instance		GParamSpec <>
default_value		ptr_t ?
cset_first		ptr_t ?
cset_nth		ptr_t ?
substitutor		gchar ?
null_fold_if_empty	guint ?
;ensure_non_null : 1	guint ?
GParamSpecString	ENDS

GParamSpecParam		STRUC
parent_instance		GParamSpec <>
GParamSpecParam		ENDS

GParamSpecBoxed		STRUC
parent_instance		GParamSpec <>
GParamSpecBoxed		ENDS

GParamSpecPointer	STRUC
parent_instance		GParamSpec <>
GParamSpecPointer	ENDS

GParamSpecValueArray	STRUC
parent_instance		GParamSpec <>
element_spec		ptr_t ?
fixed_n_elements	guint ?
GParamSpecValueArray	ENDS

GParamSpecObject	STRUC
parent_instance		GParamSpec <>
GParamSpecObject	ENDS

GParamSpecOverride	STRUC
parent_instance		GParamSpec <>
overridden		ptr_t ?
GParamSpecOverride	ENDS

GParamSpecGType		STRUC
parent_instance		GParamSpec <>
is_a_type		GType ?
GParamSpecGType		ENDS

GParamSpecVariant	STRUC
parent_instance		GParamSpec <>
type			ptr_t ?
default_value		ptr_t ?
padding			gpointer 4 dup(?)
GParamSpecVariant	ENDS

;GParamSpec*
g_param_spec_char proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gint8,
	       maximum: gint8,
	 default_value: gint8,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_uchar proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: guint8,
	       maximum: guint8,
	 default_value: guint8,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_boolean proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	 default_value: gboolean,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_int proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gint,
	       maximum: gint,
	 default_value: gint,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_uint proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: guint,
	       maximum: guint,
	 default_value: guint,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_long proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: glong,
	       maximum: glong,
	 default_value: glong,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_ulong proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gulong,
	       maximum: gulong,
	 default_value: gulong,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_int64 proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gint64,
	       maximum: gint64,
	 default_value: gint64,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_uint64 proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: guint64,
	       maximum: guint64,
	 default_value: guint64,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_unichar proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	 default_value: gunichar,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_enum proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	     enum_type: GType,
	 default_value: gint,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_flags proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	    flags_type: GType,
	 default_value: guint,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_float proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gfloat,
	       maximum: gfloat,
	 default_value: gfloat,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_double proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	       minimum: gdouble,
	       maximum: gdouble,
	 default_value: gdouble,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_string proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	 default_value: ptr gchar,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_param proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	    param_type: GType,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_boxed proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	    boxed_type: GType,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_pointer proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_value_array proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	  element_spec: ptr GParamSpec,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_object proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	   object_type: GType,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_override proto __cdecl \
		  name: ptr gchar,
	    overridden: ptr GParamSpec

;GParamSpec*
g_param_spec_gtype proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
	     is_a_type: GType,
		 flags: GParamFlags

;GParamSpec*
g_param_spec_variant proto __cdecl \
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
		  type: ptr GVariantType,
	 default_value: ptr GVariant,
		 flags: GParamFlags


ifndef GOBJECT_VAR
  ifdef G_PLATFORM_WIN32
    ifdef GOBJECT_STATIC_COMPILATION
      GOBJECT_VAR equ <>
    else
      ifdef GOBJECT_COMPILATION
	ifdef DLL_EXPORT
	  GOBJECT_VAR equ <__declspec(dllexport)>
	else
	  GOBJECT_VAR equ <extern>
	endif
      else
	GOBJECT_VAR equ <extern __declspec(dllimport)>
      endif
    endif
  else
    GOBJECT_VAR equ _GLIB_EXTERN
  endif
endif

;GOBJECT_VAR GType *g_param_spec_types;

endif

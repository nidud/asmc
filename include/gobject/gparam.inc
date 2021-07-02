ifndef __G_PARAM_H__
__G_PARAM_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc

G_TYPE_IS_PARAM macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_PARAM)>
	endm
G_PARAM_SPEC macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM, GParamSpec))>
	endm
if GLIB_VERSION_MAX_ALLOWED GE GLIB_VERSION_2_42
G_IS_PARAM_SPEC macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_FUNDAMENTAL_TYPE ((pspec), G_TYPE_PARAM))>
	endm
else
G_IS_PARAM_SPEC macro pspec
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((pspec), G_TYPE_PARAM))>
	endm
endif
G_PARAM_SPEC_CLASS macro pclass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((pclass), G_TYPE_PARAM, GParamSpecClass))>
	endm
G_IS_PARAM_SPEC_CLASS macro pclass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((pclass), G_TYPE_PARAM))>
	endm
G_PARAM_SPEC_GET_CLASS macro pspec
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((pspec), G_TYPE_PARAM, GParamSpecClass))>
	endm


G_PARAM_SPEC_TYPE macro pspec
	exitm<(G_TYPE_FROM_INSTANCE (pspec))>
	endm
G_PARAM_SPEC_TYPE_NAME macro pspec
	exitm<(g_type_name (G_PARAM_SPEC_TYPE (pspec)))>
	endm
G_PARAM_SPEC_VALUE_TYPE macro pspec
	exitm<(G_PARAM_SPEC (pspec)- GT value_type)>
	endm
G_VALUE_HOLDS_PARAM macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_PARAM))>
	endm

.enum GParamFlags {
    G_PARAM_READABLE	    = 1 shl 0,
    G_PARAM_WRITABLE	    = 1 shl 1,
    G_PARAM_READWRITE	    = (G_PARAM_READABLE or G_PARAM_WRITABLE),
    G_PARAM_CONSTRUCT	    = 1 shl 2,
    G_PARAM_CONSTRUCT_ONLY  = 1 shl 3,
    G_PARAM_LAX_VALIDATION  = 1 shl 4,
    G_PARAM_STATIC_NAME	    = 1 shl 5,
ifndef G_DISABLE_DEPRECATED
    G_PARAM_PRIVATE	    = G_PARAM_STATIC_NAME,
endif
    G_PARAM_STATIC_NICK	    = 1 shl 6,
    G_PARAM_STATIC_BLURB    = 1 shl 7,
    G_PARAM_EXPLICIT_NOTIFY = 1 shl 30,
    G_PARAM_DEPRECATED	    = 1 shl 31
}

G_PARAM_STATIC_STRINGS	equ (G_PARAM_STATIC_NAME OR G_PARAM_STATIC_NICK OR G_PARAM_STATIC_BLURB)
G_PARAM_MASK		equ (0x000000ff)
G_PARAM_USER_SHIFT	equ (8)

GParamSpec		STRUC
g_type_instance		GTypeInstance <>
name			string_t ?
flags			GParamFlags ?
value_type		GType ?
owner_type		GType ?
_nick			string_t ?
_blurb			string_t ?
qdata			ptr_t ?
ref_count		guint ?
param_id		guint ?
GParamSpec		ENDS

GParamSpecClass		STRUC
g_type_class		GTypeClass <>
value_type		GType ?
finalize		proc :ptr GParamSpec
value_set_default	proc :ptr GParamSpec, :ptr GValue
value_validate		proc :ptr GParamSpec, :ptr GValue
values_cmp		proc :ptr GParamSpec, :ptr GValue, :ptr GValue
dummy			gpointer 4 dup(?)
GParamSpecClass		ENDS

GParameter		STRUC
name			string_t ?
value			GValue <>
GParameter		ENDS


;GParamSpec*
g_param_spec_ref proto __cdecl \
		 pspec: ptr GParamSpec

;void
g_param_spec_unref proto __cdecl \
		 pspec: ptr GParamSpec

;void
g_param_spec_sink proto __cdecl \
		 pspec: ptr GParamSpec

;GParamSpec*
g_param_spec_ref_sink proto __cdecl \
		 pspec: ptr GParamSpec

;gpointer
g_param_spec_get_qdata proto __cdecl \
		 pspec: ptr GParamSpec,
		 quark: GQuark

;void
g_param_spec_set_qdata proto __cdecl \
		 pspec: ptr GParamSpec,
		 quark: GQuark,
		  data: gpointer

;void
g_param_spec_set_qdata_full proto __cdecl \
		 pspec: ptr GParamSpec,
		 quark: GQuark,
		  data: gpointer,
	       destroy: GDestroyNotify

;gpointer
g_param_spec_steal_qdata proto __cdecl \
		 pspec: ptr GParamSpec,
		 quark: GQuark

;GParamSpec*
g_param_spec_get_redirect_target proto __cdecl \
		 pspec: ptr GParamSpec


;void
g_param_value_set_default proto __cdecl \
		 pspec: ptr GParamSpec,
		 value: ptr GValue

;gboolean
g_param_value_defaults proto __cdecl \
		 pspec: ptr GParamSpec,
		 value: ptr GValue

;gboolean
g_param_value_validate proto __cdecl \
		 pspec: ptr GParamSpec,
		 value: ptr GValue

;gboolean
g_param_value_convert proto __cdecl \
		 pspec: ptr GParamSpec,
	     src_value: ptr GValue,
	    dest_value: ptr GValue,
     strict_validation: gboolean

;gint
g_param_values_cmp proto __cdecl \
		 pspec: ptr GParamSpec,
		value1: ptr GValue,
		value2: ptr GValue

g_param_spec_get_name proto __cdecl \
		 pspec: ptr GParamSpec

g_param_spec_get_nick proto __cdecl \
		 pspec: ptr GParamSpec

g_param_spec_get_blurb proto __cdecl \
		 pspec: ptr GParamSpec

g_value_set_param proto __cdecl \
		 value: ptr GValue,
		 param: ptr GParamSpec

;GParamSpec*
g_value_get_param proto __cdecl \
		 value: ptr GValue

;GParamSpec*
g_value_dup_param proto __cdecl \
		 value: ptr GValue

g_value_take_param proto __cdecl \
		 value: ptr GValue,
		 param: ptr GParamSpec

g_value_set_param_take_ownership proto __cdecl \
		 value: ptr GValue,
		 param: ptr GParamSpec

g_param_spec_get_default_value proto __cdecl \
		 pspec: ptr GParamSpec


;GQuark
g_param_spec_get_name_quark proto __cdecl \
		 pspec: ptr GParamSpec


GParamSpecTypeInfo	STRUC
instance_size		guint16 ?
n_preallocs		guint16 ?
instance_init		proc :ptr GParamSpec
value_type		GType ?
finalize		proc :ptr GParamSpec
value_set_default	proc :ptr GParamSpec, :ptr GValue
value_validate		proc :ptr GParamSpec, :ptr GValue
values_cmp		proc :ptr GParamSpec, :ptr GValue, :ptr GValue
GParamSpecTypeInfo	ENDS

;GType
g_param_type_register_static proto __cdecl \
		  name: ptr gchar,
	    pspec_info: ptr GParamSpecTypeInfo


;GType
_g_param_type_register_static_constant proto __cdecl \
		  name: string_t,
	    pspec_info: ptr GParamSpecTypeInfo,
	      opt_type: GType


;gpointer
g_param_spec_internal proto __cdecl \
	    param_type: GType,
		  name: ptr gchar,
		  nick: ptr gchar,
		 blurb: ptr gchar,
		 flags: GParamFlags

;GParamSpecPool*
g_param_spec_pool_new proto __cdecl \
	type_prefixing: gboolean

;void
g_param_spec_pool_insert proto __cdecl \
		  pool: ptr GParamSpecPool,
		 pspec: ptr GParamSpec,
	    owner_type: GType

;void
g_param_spec_pool_remove proto __cdecl \
		  pool: ptr GParamSpecPool,
		 pspec: ptr GParamSpec

;GParamSpec*
g_param_spec_pool_lookup proto __cdecl \
		  pool: ptr GParamSpecPool,
	    param_name: ptr gchar,
	    owner_type: GType,
	walk_ancestors: gboolean

;GList*
g_param_spec_pool_list_owned proto __cdecl \
		  pool: ptr GParamSpecPool,
	    owner_type: GType

;GParamSpec**
g_param_spec_pool_list proto __cdecl \
		  pool: ptr GParamSpecPool,
	    owner_type: GType,
	    n_pspecs_p: ptr guint

endif

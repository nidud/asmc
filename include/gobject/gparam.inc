ifndef __G_PARAM_H__
define __G_PARAM_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gvalue.inc

G_TYPE_IS_PARAM macro type
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_PARAM)>
  endm

G_PARAM_SPEC macro pspec
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((pspec), G_TYPE_PARAM, GParamSpec))>
  endm

if GLIB_VERSION_MAX_ALLOWED ge GLIB_VERSION_2_42
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
  exitm<(G_PARAM_SPEC (pspec).value_type)>
  endm

G_VALUE_HOLDS_PARAM macro value
  exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_PARAM))>
  endm

.enum GParamFlags {
  G_PARAM_READABLE	      = 1 shl 0,
  G_PARAM_WRITABLE	      = 1 shl 1,
  G_PARAM_READWRITE	      = (G_PARAM_READABLE or G_PARAM_WRITABLE),
  G_PARAM_CONSTRUCT	      = 1 shl 2,
  G_PARAM_CONSTRUCT_ONLY      = 1 shl 3,
  G_PARAM_LAX_VALIDATION      = 1 shl 4,
  G_PARAM_STATIC_NAME	      = 1 shl 5,
  G_PARAM_PRIVATE	      = G_PARAM_STATIC_NAME,
  G_PARAM_STATIC_NICK	      = 1 shl 6,
  G_PARAM_STATIC_BLURB	      = 1 shl 7,

  G_PARAM_EXPLICIT_NOTIFY     = 1 shl 30,

  G_PARAM_DEPRECATED	      = 1 shl 31
}


define	G_PARAM_STATIC_STRINGS (G_PARAM_STATIC_NAME or G_PARAM_STATIC_NICK or G_PARAM_STATIC_BLURB)
define	G_PARAM_MASK		(0x000000ff)
define	G_PARAM_USER_SHIFT	(8)

;GParamSpecPool		 typedef _GParamSpecPool

_GParamSpec		struct
g_type_instance		GTypeInstance <>
name			ptr gchar ?
flags			GParamFlags ?
value_type		GType ?
owner_type		GType ?
_nick			ptr gchar ?
_blurb			ptr gchar ?
qdata			ptr GData ?
ref_count		guint ?
param_id		guint ?
_GParamSpec		ends
GParamSpec		typedef _GParamSpec

_GParamSpecClass	struct
g_type_class		GTypeClass <>
value_type		GType ?
finalize		proc :ptr
value_set_default	proc :ptr, :ptr
value_validate		proc :ptr, :ptr
values_cmp		proc :ptr, :ptr, :ptr
dummy			gpointer 4 dup(?)
_GParamSpecClass	ends
GParamSpecClass		typedef _GParamSpecClass

_GParameter		struct
name			ptr gchar ?
value			GValue <>
_GParameter		ends
GParameter		typedef _GParameter

g_param_spec_ref proto :ptr
g_param_spec_unref proto :ptr
g_param_spec_sink proto :ptr
g_param_spec_ref_sink proto :ptr
g_param_spec_get_qdata proto :ptr, :GQuark
g_param_spec_set_qdata proto :ptr, :GQuark, :gpointer
g_param_spec_set_qdata_full proto :ptr, :GQuark, :gpointer, :GDestroyNotify
g_param_spec_steal_qdata proto :ptr, :GQuark
g_param_spec_get_redirect_target proto :ptr

g_param_value_set_default proto :ptr, :ptr
g_param_value_defaults proto :ptr, :ptr
g_param_value_validate proto :ptr, :ptr
g_param_value_convert proto :ptr, :ptr, :ptr, :gboolean
g_param_values_cmp proto :ptr, :ptr, :ptr
g_param_spec_get_name proto :ptr
g_param_spec_get_nick proto :ptr
g_param_spec_get_blurb proto :ptr
g_value_set_param proto :ptr, :ptr
g_value_get_param proto :ptr
g_value_dup_param proto :ptr

g_value_take_param proto :ptr, :ptr
g_value_set_param_take_ownership proto :ptr, :ptr
g_param_spec_get_default_value proto :ptr

g_param_spec_get_name_quark proto :ptr

_GParamSpecTypeInfo	struct
instance_size		guint16 ?
n_preallocs		guint16 ?
instance_init		proc :ptr
value_type		GType ?
finalize		proc :ptr
value_set_default	proc :ptr, :ptr
value_validate		proc :ptr, :ptr
values_cmp		proc :ptr, :ptr, :ptr
_GParamSpecTypeInfo	ends
GParamSpecTypeInfo	typedef _GParamSpecTypeInfo

g_param_type_register_static proto :ptr, :ptr
g_param_spec_is_valid_name proto :ptr
_g_param_type_register_static_constant proto :ptr, :ptr, :GType

g_param_spec_internal proto :GType, :ptr, :ptr, :ptr, :GParamFlags
g_param_spec_pool_new proto :gboolean
g_param_spec_pool_insert proto :ptr, :ptr, :GType
g_param_spec_pool_remove proto :ptr, :ptr
g_param_spec_pool_lookup proto :ptr, :ptr, :GType, :gboolean
g_param_spec_pool_list_owned proto :ptr, :GType
g_param_spec_pool_list proto :ptr, :GType, :ptr

endif

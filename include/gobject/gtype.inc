ifndef __G_TYPE_H__
__G_TYPE_H__ equ 1

if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc

G_TYPE_FUNDAMENTAL macro type
	exitm<(g_type_fundamental (type))>
	endm
G_TYPE_FUNDAMENTAL_MAX	equ (255 SHL G_TYPE_FUNDAMENTAL_SHIFT)

G_TYPE_INVALID		equ G_TYPE_MAKE_FUNDAMENTA (0)
G_TYPE_NONE		equ G_TYPE_MAKE_FUNDAMENTA (1)
G_TYPE_INTERFACE	equ G_TYPE_MAKE_FUNDAMENTA (2)
G_TYPE_CHAR		equ G_TYPE_MAKE_FUNDAMENTA (3)
G_TYPE_UCHAR		equ G_TYPE_MAKE_FUNDAMENTA (4)
G_TYPE_BOOLEAN		equ G_TYPE_MAKE_FUNDAMENTA (5)
G_TYPE_INT		equ G_TYPE_MAKE_FUNDAMENTA (6)
G_TYPE_UINT		equ G_TYPE_MAKE_FUNDAMENTA (7)
G_TYPE_LONG		equ G_TYPE_MAKE_FUNDAMENTA (8)
G_TYPE_ULONG		equ G_TYPE_MAKE_FUNDAMENTA (9)
G_TYPE_INT64		equ G_TYPE_MAKE_FUNDAMENTA (10)
G_TYPE_UINT64		equ G_TYPE_MAKE_FUNDAMENTA (11)
G_TYPE_ENUM		equ G_TYPE_MAKE_FUNDAMENTA (12)
G_TYPE_FLAGS		equ G_TYPE_MAKE_FUNDAMENTA (13)
G_TYPE_FLOAT		equ G_TYPE_MAKE_FUNDAMENTA (14)
G_TYPE_DOUBLE		equ G_TYPE_MAKE_FUNDAMENTA (15)
G_TYPE_STRING		equ G_TYPE_MAKE_FUNDAMENTA (16)
G_TYPE_POINTER		equ G_TYPE_MAKE_FUNDAMENTA (17)
G_TYPE_BOXED		equ G_TYPE_MAKE_FUNDAMENTA (18)
G_TYPE_PARAM		equ G_TYPE_MAKE_FUNDAMENTA (19)
G_TYPE_OBJECT		equ G_TYPE_MAKE_FUNDAMENTA (20)
G_TYPE_VARIANT		equ G_TYPE_MAKE_FUNDAMENTA (21)


G_TYPE_FUNDAMENTAL_SHIFT equ (2)
G_TYPE_MAKE_FUNDAMENTAL macro x
	exitm<((GType) ((x) SHL G_TYPE_FUNDAMENTAL_SHIFT))>
	endm
G_TYPE_RESERVED_GLIB_FIRST equ (22)
G_TYPE_RESERVED_GLIB_LAST equ (31)
G_TYPE_RESERVED_BSE_FIRST equ (32)
G_TYPE_RESERVED_BSE_LAST equ (48)
G_TYPE_RESERVED_USER_FIRST equ (49)


G_TYPE_IS_FUNDAMENTAL macro type
	exitm<((type) LE G_TYPE_FUNDAMENTAL_MAX)>
	endm
G_TYPE_IS_DERIVED macro type
	exitm<((type) GT G_TYPE_FUNDAMENTAL_MAX)>
	endm
G_TYPE_IS_INTERFACE macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_INTERFACE)>
	endm
G_TYPE_IS_CLASSED macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_CLASSED))>
	endm
G_TYPE_IS_INSTANTIATABLE macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_INSTANTIATABLE))>
	endm
G_TYPE_IS_DERIVABLE macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_DERIVABLE))>
	endm
G_TYPE_IS_DEEP_DERIVABLE macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_DEEP_DERIVABLE))>
	endm
G_TYPE_IS_ABSTRACT macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_ABSTRACT))>
	endm
G_TYPE_IS_VALUE_ABSTRACT macro type
	exitm<(g_type_test_flags ((type), G_TYPE_FLAG_VALUE_ABSTRACT))>
	endm
G_TYPE_IS_VALUE_TYPE macro type
	exitm<(g_type_check_is_value_type (type))>
	endm
G_TYPE_HAS_VALUE_TABLE macro type
	exitm<(g_type_value_table_peek (type) NOT = NULL)>
	endm


if GLIB_SIZEOF_SIZE_T NE GLIB_SIZEOF_LONG OR NOT defined(__cplusplus)
GType			typedef gsize
else
GType			typedef gulong
endif

;GValue			typedef GValue
;GTypeCValue		typedef union  _GTypeCValue
;GTypePlugin		typedef GTypePlugin
;GTypeClass		typedef GTypeClass
;GTypeInterface		typedef GTypeInterface
;GTypeInstance		typedef GTypeInstance
;GTypeInfo		typedef GTypeInfo
;GTypeFundamentalInfo	typedef GTypeFundamentalInfo
;GInterfaceInfo		typedef GInterfaceInfo
;GTypeValueTable		typedef GTypeValueTable
;GTypeQuery		typedef GTypeQuery


GTypeClass		STRUC
g_type			GType ?
GTypeClass		ENDS

GTypeInstance		STRUC
g_class			ptr_t ?
GTypeInstance		ENDS

GTypeInterface		STRUC
g_type			GType ?
g_instance_type		GType ?
GTypeInterface		ENDS

GTypeQuery		STRUC
type			GType ?
type_name		string_t ?
class_size		guint ?
instance_size		guint ?
GTypeQuery		ENDS


G_TYPE_CHECK_INSTANCE macro instance
	exitm<(_G_TYPE_CHI ((GTypeInstance*) (instance)))>
	endm
G_TYPE_CHECK_INSTANCE_CAST macro instance, g_type, c_type
	exitm<(_G_TYPE_CIC ((instance), (g_type), c_type))>
	endm
G_TYPE_CHECK_INSTANCE_TYPE macro instance, g_type
	exitm<(_G_TYPE_CIT ((instance), (g_type)))>
	endm
G_TYPE_CHECK_INSTANCE_FUNDAMENTAL_TYPE macro instance, g_type
	exitm<(_G_TYPE_CIFT ((instance), (g_type)))>
	endm
G_TYPE_INSTANCE_GET_CLASS macro instance, g_type, c_type
	exitm<(_G_TYPE_IGC ((instance), (g_type), c_type))>
	endm
G_TYPE_INSTANCE_GET_INTERFACE macro instance, g_type, c_type
	exitm<(_G_TYPE_IGI ((instance), (g_type), c_type))>
	endm
G_TYPE_CHECK_CLASS_CAST macro g_class, g_type, c_type
	exitm<(_G_TYPE_CCC ((g_class), (g_type), c_type))>
	endm
G_TYPE_CHECK_CLASS_TYPE macro g_class, g_type
	exitm<(_G_TYPE_CCT ((g_class), (g_type)))>
	endm
G_TYPE_CHECK_VALUE macro value
	exitm<(_G_TYPE_CHV ((value)))>
	endm
G_TYPE_CHECK_VALUE_TYPE macro value, g_type
	exitm<(_G_TYPE_CVH ((value), (g_type)))>
	endm
G_TYPE_FROM_INSTANCE macro instance
	exitm<(G_TYPE_FROM_CLASS (((GTypeInstance*) (instance))- GT g_class))>
	endm
G_TYPE_FROM_CLASS macro g_class
	exitm<(((GTypeClass*) (g_class))- GT g_type)>
	endm
G_TYPE_FROM_INTERFACE macro g_iface
	exitm<(((GTypeInterface*) (g_iface))- GT g_type)>
	endm

G_TYPE_INSTANCE_GET_PRIVATE macro instance, g_type, c_type
	exitm<((c_type*) g_type_instance_get_private ((GTypeInstance*) (instance), (g_type)))>
	endm

G_TYPE_CLASS_GET_PRIVATE macro klass, g_type, c_type
	exitm<((c_type*) g_type_class_get_private ((GTypeClass*) (klass), (g_type)))>
	endm

.enum GTypeDebugFlags {
	G_TYPE_DEBUG_NONE	= 0,
	G_TYPE_DEBUG_OBJECTS	= 1 shl 0,
	G_TYPE_DEBUG_SIGNALS	= 1 shl 1,
	G_TYPE_DEBUG_INSTANCE_COUNT = 1 shl 2,
	G_TYPE_DEBUG_MASK	= 0x07
}


g_type_init proto __cdecl
g_type_init_with_debug_flags proto __cdecl \
	   debug_flags: GTypeDebugFlags

g_type_name proto __cdecl \
		  type: GType

;GQuark
g_type_qname proto __cdecl \
		  type: GType

;GType
g_type_from_name proto __cdecl \
		  name: ptr gchar

;GType
g_type_parent proto __cdecl \
		  type: GType

;guint
g_type_depth proto __cdecl \
		  type: GType

;GType
g_type_next_base proto __cdecl \
	     leaf_type: GType,
	     root_type: GType

;gboolean
g_type_is_a proto __cdecl \
		  type: GType,
	     is_a_type: GType

;gpointer
g_type_class_ref proto __cdecl \
		  type: GType

;gpointer
g_type_class_peek proto __cdecl \
		  type: GType

;gpointer
g_type_class_peek_static proto __cdecl \
		  type: GType

;void
g_type_class_unref proto __cdecl \
	       g_class: gpointer

;gpointer
g_type_class_peek_parent proto __cdecl \
	       g_class: gpointer

;gpointer
g_type_interface_peek proto __cdecl \
	instance_class: gpointer,
	    iface_type: GType

;gpointer
g_type_interface_peek_parent proto __cdecl \
	       g_iface: gpointer


;gpointer
g_type_default_interface_ref proto __cdecl \
		g_type: GType

;gpointer
g_type_default_interface_peek proto __cdecl \
		g_type: GType

;void
g_type_default_interface_unref proto __cdecl \
	       g_iface: gpointer


;GType*
g_type_children proto __cdecl \
		  type: GType,
	    n_children: ptr guint

;GType*
g_type_interfaces proto __cdecl \
		  type: GType,
	  n_interfaces: ptr guint


;void
g_type_set_qdata proto __cdecl \
		  type: GType,
		 quark: GQuark,
		  data: gpointer

;gpointer
g_type_get_qdata proto __cdecl \
		  type: GType,
		 quark: GQuark

;void
g_type_query proto __cdecl \
		  type: GType,
		 query: ptr GTypeQuery


;int
g_type_get_instance_count proto __cdecl \
		  type: GType


CALLBACKC(GBaseInitFunc, :gpointer)
CALLBACKC(GBaseFinalizeFunc, :gpointer)
CALLBACKC(GClassInitFunc, :gpointer)
CALLBACKC(GClassFinalizeFunc, :gpointer)
CALLBACKC(GInstanceInitFunc, :GTypeInstance)
CALLBACKC(GInterfaceInitFunc, :gpointer)
CALLBACKC(GInterfaceFinalizeFunc, :gpointer)
CALLBACKC(GTypeClassCacheFunc, :gpointer)
CALLBACKC(GTypeInterfaceCheckFunc, :gpointer)

.enum GTypeFundamentalFlags {
    G_TYPE_FLAG_CLASSED = (1 shl 0),
    G_TYPE_FLAG_INSTANTIATABLE = (1 shl 1),
    G_TYPE_FLAG_DERIVABLE = (1 shl 2),
    G_TYPE_FLAG_DEEP_DERIVABLE = (1 shl 3)
}

.enum GTypeFlags {
    G_TYPE_FLAG_ABSTRACT = (1 shl 4),
    G_TYPE_FLAG_VALUE_ABSTRACT = (1 shl 5)
}

GTypeInfo		STRUC
class_size		guint16 ?
base_init		GBaseInitFunc ?
base_finalize		GBaseFinalizeFunc ?
class_init		GClassInitFunc ?
class_finalize		GClassFinalizeFunc ?
class_data		gconstpointer ?
instance_size		guint16 ?
n_preallocs		guint16 ?
instance_init		GInstanceInitFunc ?
value_table		ptr_t ?
GTypeInfo		ENDS

GTypeFundamentalInfo	STRUC
type_flags		GTypeFundamentalFlags ?
GTypeFundamentalInfo	ENDS

GInterfaceInfo		STRUC
interface_init		GInterfaceInitFunc ?
interface_finalize	GInterfaceFinalizeFunc ?
interface_data		gpointer ?
GInterfaceInfo		ENDS

GTypeValueTable		STRUC
value_init		proc :ptr GValue
value_free		proc :ptr GValue
value_copy		proc :ptr GValue, :ptr GValue
value_peek_pointer	proc :ptr
collect_format		string_t ?
collect_value		proc :ptr, :guint, :ptr, :guint
lcopy_format		string_t ?
lcopy_value		proc :ptr, :guint, :ptr, :guint
GTypeValueTable		ENDS

;GType
g_type_register_static proto __cdecl \
	   parent_type: GType,
	     type_name: ptr gchar,
		  info: ptr GTypeInfo,
		 flags: GTypeFlags

;GType
g_type_register_static_simple proto __cdecl \
	   parent_type: GType,
	     type_name: ptr gchar,
	    class_size: guint,
	    class_init: GClassInitFunc,
	 instance_size: guint,
	 instance_init: GInstanceInitFunc,
		 flags: GTypeFlags


;GType
g_type_register_dynamic proto __cdecl \
	   parent_type: GType,
	     type_name: ptr gchar,
		plugin: ptr GTypePlugin,
		 flags: GTypeFlags

;GType
g_type_register_fundamental proto __cdecl \
	       type_id: GType,
	     type_name: ptr gchar,
		  info: ptr GTypeInfo,
		 finfo: ptr GTypeFundamentalInfo,
		 flags: GTypeFlags

;void
g_type_add_interface_static proto __cdecl \
	 instance_type: GType,
	interface_type: GType,
		  info: ptr GInterfaceInfo

;void
g_type_add_interface_dynamic proto __cdecl \
	 instance_type: GType,
	interface_type: GType,
		plugin: ptr GTypePlugin

;void
g_type_interface_add_prerequisite proto __cdecl \
	interface_type: GType,
     prerequisite_type: GType

;GType*
g_type_interface_prerequisites proto __cdecl \
	interface_type: GType,
       n_prerequisites: ptr guint

;void
g_type_class_add_private proto __cdecl \
	       g_class: gpointer,
	  private_size: gsize

;gint
g_type_add_instance_private proto __cdecl \
	    class_type: GType,
	  private_size: gsize

;gpointer
g_type_instance_get_private proto __cdecl \
	      instance: ptr GTypeInstance,
	  private_type: GType

;void
g_type_class_adjust_private_offset proto __cdecl \
	       g_class: gpointer,
private_size_or_offset: ptr gint


;void
g_type_add_class_private proto __cdecl \
	    class_type: GType,
	  private_size: gsize

;gpointer
g_type_class_get_private proto __cdecl \
		 klass: ptr GTypeClass,
	  private_type: GType

;gint
g_type_class_get_instance_private_offset proto __cdecl \
	       g_class: gpointer


;void
g_type_ensure proto __cdecl \
		  type: GType

;guint
g_type_get_type_registration_serial proto __cdecl



G_DEFINE_TYPE macro TN, t_n, T_P
	exitm<.err>
	endm
G_DEFINE_TYPE_WITH_CODE macro TN, t_n, T_P, _C_
	exitm<.err>
	endm
G_DEFINE_TYPE_WITH_PRIVATE macro TN, t_n, T_P
	exitm<G_DEFINE_TYPE_EXTENDED (TN, t_n, T_P, 0, G_ADD_PRIVATE (TN))>
	endm
G_DEFINE_ABSTRACT_TYPE macro TN, t_n, T_P
	exitm<G_DEFINE_TYPE_EXTENDED (TN, t_n, T_P, G_TYPE_FLAG_ABSTRACT, {})>
	endm
G_DEFINE_ABSTRACT_TYPE_WITH_CODE macro TN, t_n, T_P, _C_
	exitm<.err>
	endm
G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE macro TN, t_n, T_P
	exitm<G_DEFINE_TYPE_EXTENDED (TN, t_n, T_P, G_TYPE_FLAG_ABSTRACT, G_ADD_PRIVATE (TN))>
	endm
G_DEFINE_TYPE_EXTENDED macro TN, t_n, T_P, _f_, _C_
	exitm<.err>
	endm

G_DEFINE_INTERFACE macro TN, t_n, T_P
	exitm<G_DEFINE_INTERFACE_WITH_CODE(TN, t_n, T_P)>
	endm

G_DEFINE_INTERFACE_WITH_CODE macro TN, t_n, T_P, _C_
	exitm<.err>
	endm

G_IMPLEMENT_INTERFACE macro TYPE_IFACE, iface_init
	exitm<.err>
	endm

G_ADD_PRIVATE macro TypeName
	exitm<.err>
	endm

G_PRIVATE_OFFSET macro TypeName, field
	exitm<.err>
	endm

G_PRIVATE_FIELD_P macro TypeName, inst, field_name
	exitm<.err>
	endm

G_PRIVATE_FIELD macro TypeName, inst, field_type, field_name
	exitm<.err>
	endm

if GLIB_VERSION_MAX_ALLOWED GE GLIB_VERSION_2_38
_G_DEFINE_TYPE_EXTENDED_CLASS_INIT macro TypeName, type_name
	exitm<.err>
	endm
else
_G_DEFINE_TYPE_EXTENDED_CLASS_INIT macro TypeName, type_name
	exitm<.err>
	endm
endif

_G_DEFINE_TYPE_EXTENDED_BEGIN macro TypeName, type_name, TYPE_PARENT, flags
	exitm<.err>
	endm

_G_DEFINE_TYPE_EXTENDED_END macro
	exitm<.err>
	endm

_G_DEFINE_INTERFACE_EXTENDED_BEGIN macro TypeName, type_name, TYPE_PREREQ
	exitm<.err>
	endm

_G_DEFINE_INTERFACE_EXTENDED_END macro
	exitm<.err>
	endm

G_DEFINE_BOXED_TYPE macro TypeName, type_name, copy_func, free_func
	exitm<.err>
	endm
G_DEFINE_BOXED_TYPE_WITH_CODE macro TypeName, type_name, copy_func, free_func, _C_
	exitm<.err>
	endm

_G_DEFINE_BOXED_TYPE_BEGIN macro TypeName, type_name, copy_func, free_func
	exitm<.err>
	endm

G_DEFINE_POINTER_TYPE macro TypeName, type_name
	exitm<G_DEFINE_POINTER_TYPE_WITH_CODE (TypeName, type_name, {})>
	endm
G_DEFINE_POINTER_TYPE_WITH_CODE macro TypeName, type_name, _C_
	exitm<.err>
	endm

_G_DEFINE_POINTER_TYPE_BEGIN macro TypeName, type_name
	exitm<.err>
	endm

;GTypePlugin*
g_type_get_plugin proto __cdecl \
		  type: GType

;GTypePlugin*
g_type_interface_get_plugin proto __cdecl \
	 instance_type: GType,
	interface_type: GType

;GType
g_type_fundamental_next proto __cdecl
;GType
g_type_fundamental proto __cdecl \
	       type_id: GType

;GTypeInstance*
g_type_create_instance proto __cdecl \
		  type: GType

;void
g_type_free_instance proto __cdecl \
	      instance: ptr GTypeInstance


;void
g_type_add_class_cache_func proto __cdecl \
	    cache_data: gpointer,
	    cache_func: GTypeClassCacheFunc

;void
g_type_remove_class_cache_func proto __cdecl \
	    cache_data: gpointer,
	    cache_func: GTypeClassCacheFunc

;void
g_type_class_unref_uncached proto __cdecl \
	       g_class: gpointer


;void
g_type_add_interface_check proto __cdecl \
	    check_data: gpointer,
	    check_func: GTypeInterfaceCheckFunc

;void
g_type_remove_interface_check proto __cdecl \
	    check_data: gpointer,
	    check_func: GTypeInterfaceCheckFunc


;GTypeValueTable*
g_type_value_table_peek proto __cdecl \
		  type: GType



;gboolean
g_type_check_instance proto __cdecl \
	      instance: ptr GTypeInstance

;GTypeInstance*
g_type_check_instance_cast proto __cdecl \
	      instance: ptr GTypeInstance,
	    iface_type: GType

;gboolean
g_type_check_instance_is_a proto __cdecl \
	      instance: ptr GTypeInstance,
	    iface_type: GType

;gboolean
g_type_check_instance_is_fundamentally_a proto __cdecl \
	      instance: ptr GTypeInstance,
      fundamental_type: GType

;GTypeClass*
g_type_check_class_cast proto __cdecl \
	       g_class: ptr GTypeClass,
	     is_a_type: GType

;gboolean
g_type_check_class_is_a proto __cdecl \
	       g_class: ptr GTypeClass,
	     is_a_type: GType
;gboolean
g_type_check_is_value_type proto __cdecl \
		  type: GType

;gboolean
g_type_check_value proto __cdecl \
		 value: ptr GValue
;gboolean
g_type_check_value_holds proto __cdecl \
		 value: ptr GValue,
		  type: GType
;gboolean
g_type_test_flags proto __cdecl \
		  type: GType,
		 flags: guint

;const
g_type_name_from_instance proto __cdecl \
	      instance: ptr GTypeInstance

;const
g_type_name_from_class proto __cdecl \
	       g_class: ptr GTypeClass



ifndef G_DISABLE_CAST_CHECKS
  ;_G_TYPE_CIC(ip, gt, ct) equ ((ct*) g_type_check_instance_cast ((GTypeInstance*) ip, gt))
  ;_G_TYPE_CCC(cp, gt, ct) equ ((ct*) g_type_check_class_cast ((GTypeClass*) cp, gt))
else
  ;_G_TYPE_CIC(ip, gt, ct) equ ((ct*) ip)
  ;_G_TYPE_CCC(cp, gt, ct) equ ((ct*) cp)
endif
_G_TYPE_CHI macro ip
	exitm<(g_type_check_instance ((GTypeInstance*) ip))>
	endm
_G_TYPE_CHV macro vl
	exitm<(g_type_check_value ((GValue*) vl))>
	endm
_G_TYPE_IGC macro ip, gt, ct
	exitm<((ct*) (((GTypeInstance*) ip)- GT g_class))>
	endm
_G_TYPE_IGI macro ip, gt, ct
	exitm<((ct*) g_type_interface_peek (((GTypeInstance*) ip)- GT g_class, gt))>
	endm
_G_TYPE_CIFT macro ip, ft
	exitm<(g_type_check_instance_is_fundamentally_a ((GTypeInstance*) ip, ft))>
	endm
ifdef	__GNUC__
  ;_G_TYPE_CIT(ip, gt) equ (G_GNUC_EXTENSION ({ GTypeInstance *__inst = (GTypeInstance*) ip; GType __t = gt; gboolean __r;   if ( NOT __inst)	    __r = FALSE;   else if (__inst- GT g_class AND __inst- GT g_class- GT g_type EQ __t)     __r = TRUE;   else	    __r = g_type_check_instance_is_a (__inst, __t);   __r; }))
  ;_G_TYPE_CCT(cp, gt) equ (G_GNUC_EXTENSION ({ GTypeClass *__class = (GTypeClass*) cp; GType __t = gt; gboolean __r;	  if ( NOT __class)	__r = FALSE;   else if (__class- GT g_type EQ __t)     __r = TRUE;   else     __r = g_type_check_class_is_a (__class, __t);   __r; }))
  ;_G_TYPE_CVH(vl, gt) equ (G_GNUC_EXTENSION ({ GValue *__val = (GValue*) vl; GType __t = gt; gboolean __r;	if ( NOT __val)	    __r = FALSE;   else if (__val- GT g_type EQ __t)	 __r = TRUE;   else	__r = g_type_check_value_holds (__val, __t);   __r; }))
else
  ;_G_TYPE_CIT(ip, gt) equ (g_type_check_instance_is_a ((GTypeInstance*) ip, gt))
  ;_G_TYPE_CCT(cp, gt) equ (g_type_check_class_is_a ((GTypeClass*) cp, gt))
  ;_G_TYPE_CVH(vl, gt) equ (g_type_check_value_holds ((GValue*) vl, gt))
endif
G_TYPE_FLAG_RESERVED_ID_BIT equ (1 SHL 0)

endif

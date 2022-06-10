ifndef __G_TYPE_H__
define __G_TYPE_H__

if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include glib.inc

G_TYPE_FUNDAMENTAL macro type
  exitm<(g_type_fundamental (type))>
  endm

define G_TYPE_FUNDAMENTAL_SHIFT 2
define G_TYPE_FUNDAMENTAL_MAX	(255 shl G_TYPE_FUNDAMENTAL_SHIFT)

G_TYPE_MAKE_FUNDAMENTAL macro x
  exitm<((x) shl G_TYPE_FUNDAMENTAL_SHIFT)>
  endm

define G_TYPE_INVALID		G_TYPE_MAKE_FUNDAMENTAL (0)
define G_TYPE_NONE		G_TYPE_MAKE_FUNDAMENTAL (1)
define G_TYPE_INTERFACE		G_TYPE_MAKE_FUNDAMENTAL (2)
define G_TYPE_CHAR		G_TYPE_MAKE_FUNDAMENTAL (3)
define G_TYPE_UCHAR		G_TYPE_MAKE_FUNDAMENTAL (4)
define G_TYPE_BOOLEAN		G_TYPE_MAKE_FUNDAMENTAL (5)
define G_TYPE_INT		G_TYPE_MAKE_FUNDAMENTAL (6)
define G_TYPE_UINT		G_TYPE_MAKE_FUNDAMENTAL (7)
define G_TYPE_LONG		G_TYPE_MAKE_FUNDAMENTAL (8)
define G_TYPE_ULONG		G_TYPE_MAKE_FUNDAMENTAL (9)
define G_TYPE_INT64		G_TYPE_MAKE_FUNDAMENTAL (10)
define G_TYPE_UINT64		G_TYPE_MAKE_FUNDAMENTAL (11)
define G_TYPE_ENUM		G_TYPE_MAKE_FUNDAMENTAL (12)
define G_TYPE_FLAGS		G_TYPE_MAKE_FUNDAMENTAL (13)
define G_TYPE_FLOAT		G_TYPE_MAKE_FUNDAMENTAL (14)
define G_TYPE_DOUBLE		G_TYPE_MAKE_FUNDAMENTAL (15)
define G_TYPE_STRING		G_TYPE_MAKE_FUNDAMENTAL (16)
define G_TYPE_POINTER		G_TYPE_MAKE_FUNDAMENTAL (17)
define G_TYPE_BOXED		G_TYPE_MAKE_FUNDAMENTAL (18)
define G_TYPE_PARAM		G_TYPE_MAKE_FUNDAMENTAL (19)
define G_TYPE_OBJECT		G_TYPE_MAKE_FUNDAMENTAL (20)
define G_TYPE_VARIANT		G_TYPE_MAKE_FUNDAMENTAL (21)

define G_TYPE_RESERVED_GLIB_FIRST   22
define G_TYPE_RESERVED_GLIB_LAST    31
define G_TYPE_RESERVED_BSE_FIRST    32
define G_TYPE_RESERVED_BSE_LAST	    48
define G_TYPE_RESERVED_USER_FIRST   49

G_TYPE_IS_FUNDAMENTAL macro type
  exitm<((type) le G_TYPE_FUNDAMENTAL_MAX)>
  endm
G_TYPE_IS_DERIVED macro type
  exitm<((type) gt G_TYPE_FUNDAMENTAL_MAX)>
  endm
G_TYPE_IS_INTERFACE macro type
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_INTERFACE)>
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
  exitm<(g_type_value_table_peek (type))>
  endm
G_TYPE_IS_FINAL macro type
  exitm<(g_type_test_flags ((type), G_TYPE_FLAG_FINAL)) GLIB_AVAILABLE_MACRO_IN_2_70>
  endm


if GLIB_SIZEOF_SIZE_T ne GLIB_SIZEOF_LONG or not defined(__cplusplus)
GType typedef gsize
else
GType typedef gulong
endif

.enum GTypeDebugFlags {
  G_TYPE_DEBUG_NONE	= 0,
  G_TYPE_DEBUG_OBJECTS	= 1 shl 0,
  G_TYPE_DEBUG_SIGNALS	= 1 shl 1,
  G_TYPE_DEBUG_INSTANCE_COUNT = 1 shl 2,
  G_TYPE_DEBUG_MASK	= 0x07
}

_GTypeClass		struct
g_type			GType ?
_GTypeClass		ends
GTypeClass		typedef _GTypeClass

_GTypeInstance		struct
g_class			ptr GTypeClass ?
_GTypeInstance		ends
GTypeInstance		typedef _GTypeInstance

_GTypeInterface		struct
g_type			GType ?
g_instance_type		GType ?
_GTypeInterface		ends
GTypeInterface		typedef _GTypeInterface

_GTypeQuery		struct
type			GType ?
type_name		ptr gchar ?
class_size		guint ?
instance_size		guint ?
_GTypeQuery		ends
GTypeQuery		typedef _GTypeQuery


G_TYPE_CHECK_INSTANCE macro instance
	exitm<_G_TYPE_CHI(instance)>
	endm
G_TYPE_CHECK_INSTANCE_CAST macro instance, g_type, c_type
	exitm<_G_TYPE_CIC (instance, g_type, c_type)>
	endm
G_TYPE_CHECK_INSTANCE_TYPE macro instance, g_type
	exitm<_G_TYPE_CIT (instance, g_type)>
	endm
G_TYPE_CHECK_INSTANCE_FUNDAMENTAL_TYPE macro instance, g_type
	exitm<_G_TYPE_CIFT (instance, g_type)>
	endm
G_TYPE_INSTANCE_GET_CLASS macro instance, g_type, c_type
	exitm<_G_TYPE_IGC (instance, g_type, c_type)>
	endm
G_TYPE_INSTANCE_GET_INTERFACE macro instance, g_type, c_type
	exitm<_G_TYPE_IGI (instance, g_type, c_type)>
	endm
G_TYPE_CHECK_CLASS_CAST macro g_class, g_type, c_type
	exitm<_G_TYPE_CCC (g_class, g_type, c_type)>
	endm
G_TYPE_CHECK_CLASS_TYPE macro g_class, g_type
	exitm<_G_TYPE_CCT (g_class, g_type)>
	endm
G_TYPE_CHECK_VALUE macro value
	exitm<_G_TYPE_CHV (value)>
	endm
G_TYPE_CHECK_VALUE_TYPE macro value, g_type
	exitm<_G_TYPE_CVH (value, g_type)>
	endm
G_TYPE_FROM_INSTANCE macro instance
	mov rax,instance
	exitm<G_TYPE_FROM_CLASS ([rax].GTypeInstance.g_class)>
	endm
G_TYPE_FROM_CLASS macro g_class
	mov rax,g_class
	exitm<[rax].GTypeClass.g_type>
	endm
G_TYPE_FROM_INTERFACE macro g_iface
	mov rax,g_iface
	exitm<([rax].GTypeInterface.g_type)>
	endm

G_TYPE_INSTANCE_GET_PRIVATE macro instance, g_type, c_type
	exitm<g_type_instance_get_private ((instance), g_type())>
	endm

G_TYPE_CLASS_GET_PRIVATE macro klass, g_type, c_type
	exitm<g_type_class_get_private ((klass), g_type())>
	endm

.enum GTypeDebugFlags {
    G_TYPE_DEBUG_NONE	    = 0,
    G_TYPE_DEBUG_OBJECTS    = 1 shl 0,
    G_TYPE_DEBUG_SIGNALS    = 1 shl 1,
    G_TYPE_DEBUG_INSTANCE_COUNT = 1 shl 2,
    G_TYPE_DEBUG_MASK	    = 0x07
    }


g_type_init proto
g_type_init_with_debug_flags proto :GTypeDebugFlags
g_type_name proto :GType
g_type_qname proto :GType
g_type_from_name proto :ptr
g_type_parent proto :GType
g_type_depth proto :GType
g_type_next_base proto :GType, :GType
g_type_is_a proto :GType, :GType
g_type_class_ref proto :GType
g_type_class_peek proto :GType
g_type_class_peek_static proto :GType
g_type_class_unref proto :gpointer
g_type_class_peek_parent proto :gpointer
g_type_interface_peek proto :gpointer, :GType
g_type_interface_peek_parent proto :gpointer

g_type_default_interface_ref proto :GType
g_type_default_interface_peek proto :GType
g_type_default_interface_unref proto :gpointer

g_type_children proto :GType, :ptr
g_type_interfaces proto :GType, :ptr

g_type_set_qdata proto :GType, :GQuark, :gpointer
g_type_get_qdata proto :GType, :GQuark
g_type_query proto :GType, :ptr

g_type_get_instance_count proto :GType

CALLBACK(GBaseInitFunc, :gpointer)
CALLBACK(GBaseFinalizeFunc, :gpointer)
CALLBACK(GClassInitFunc, :gpointer, :gpointer)
CALLBACK(GClassFinalizeFunc, :gpointer, :gpointer)
CALLBACK(GInstanceInitFunc, :ptr, :gpointer)
CALLBACK(GInterfaceInitFunc, :gpointer, :gpointer)
CALLBACK(GInterfaceFinalizeFunc, :gpointer, :gpointer)
CALLBACK(GTypeClassCacheFunc, :gpointer, :ptr)
CALLBACK(GTypeInterfaceCheckFunc, :gpointer, :gpointer)

.enum GTypeFundamentalFlags {
  G_TYPE_FLAG_CLASSED		= (1 shl 0),
  G_TYPE_FLAG_INSTANTIATABLE	= (1 shl 1),
  G_TYPE_FLAG_DERIVABLE		= (1 shl 2),
  G_TYPE_FLAG_DEEP_DERIVABLE	= (1 shl 3)
}

.enum GTypeFlags {
  G_TYPE_FLAG_ABSTRACT = (1 shl 4),
  G_TYPE_FLAG_VALUE_ABSTRACT = (1 shl 5),
  G_TYPE_FLAG_FINAL = (1 shl 6)
}

_GTypeValueTable	struct
value_init		proc :ptr
value_free		proc :ptr
value_copy		proc :ptr, :ptr
value_peek_pointer	proc :ptr
collect_format		ptr gchar ?
collect_value		proc :ptr, :guint, :ptr, :guint
lcopy_format		ptr gchar ?
lcopy_value		proc :ptr, :guint, :ptr, :guint
_GTypeValueTable	ends
GTypeValueTable		typedef GTypeValueTable

_GTypeInfo		struct
class_size		guint16 ?
base_init		GBaseInitFunc ?
base_finalize		GBaseFinalizeFunc ?
class_init		GClassInitFunc ?
class_finalize		GClassFinalizeFunc ?
class_data		gconstpointer ?
instance_size		guint16 ?
n_preallocs		guint16 ?
instance_init		GInstanceInitFunc ?
value_table		ptr GTypeValueTable ?
_GTypeInfo		ends
GTypeInfo		typedef GTypeInfo

;GValue			typedef GValue
;GTypeCValue		typedef union  _GTypeCValue
;GTypePlugin		typedef GTypePlugin

_GTypeFundamentalInfo	struct
type_flags		GTypeFundamentalFlags ?
_GTypeFundamentalInfo	ends
GTypeFundamentalInfo	typedef GTypeFundamentalInfo

_GInterfaceInfo		struct
interface_init		GInterfaceInitFunc ?
interface_finalize	GInterfaceFinalizeFunc ?
interface_data		gpointer ?
_GInterfaceInfo		ends
GInterfaceInfo		typedef GInterfaceInfo

g_type_register_static proto :GType, :ptr, :ptr, :GTypeFlags
g_type_register_static_simple proto :GType, :ptr, :guint, :GClassInitFunc, :guint, :GInstanceInitFunc, :GTypeFlags

g_type_register_dynamic proto :GType, :ptr, :ptr, :GTypeFlags
g_type_register_fundamental proto :GType, :ptr, :ptr, :ptr, :GTypeFlags
g_type_add_interface_static proto :GType, :GType, :ptr
g_type_add_interface_dynamic proto :GType, :GType, :ptr
g_type_interface_add_prerequisite proto :GType, :GType
g_type_interface_prerequisites proto :GType, :ptr
g_type_interface_instantiatable_prerequisite proto :GType
g_type_class_add_private proto :gpointer, :gsize
g_type_add_instance_private proto :GType, :gsize
g_type_instance_get_private proto :ptr, :GType
g_type_class_adjust_private_offset proto :gpointer, :ptr

g_type_add_class_private proto :GType, :gsize
g_type_class_get_private proto :ptr, :GType
g_type_class_get_instance_private_offset proto :gpointer

g_type_ensure proto :GType
g_type_get_type_registration_serial proto

G_DECLARE_FINAL_TYPE macro ModuleObjName, module_obj_name, MODULE, OBJ_NAME, ParentName

  &module_obj_name&_get_type proto
  ModuleObjName typedef _&ModuleObjName&

  &ModuleObjName&Class struct
  parent_class &ParentName&Class <>
  &ModuleObjName&Class ends

  _GLIB_DEFINE_AUTOPTR_CHAINUP(ModuleObjName, ParentName)
  G_DEFINE_AUTOPTR_CLEANUP_FUNC(&ModuleObjName&Class, g_type_class_unref)

  &MODULE&_&OBJ_NAME& proto :gpointer {
    G_TYPE_CHECK_INSTANCE_CAST(_1, &module_obj_name&_get_type(), ModuleObjName)
    }
  &MODULE&_IS_&OBJ_NAME& proto :gpointer {
    G_TYPE_CHECK_INSTANCE_TYPE(_1, &module_obj_name&_get_type())
    }
  exitm<>
  endm

G_DEFINE_TYPE macro TN, t_n, T_P
	exitm<G_DEFINE_TYPE_EXTENDED(TN, t_n, T_P, 0, {})>
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
	_G_DEFINE_TYPE_EXTENDED_BEGIN(TN, t_n, T_P, _f_)
	;_C_
	;_G_DEFINE_TYPE_EXTENDED_END()
	exitm<>
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

_G_DEFINE_TYPE_EXTENDED_CLASS_INIT macro TypeName, type_name
    &type_name&_class_intern_init proc private uses rbx klass:gpointer
	mov rbx,klass
	mov &type_name&_parent_class,g_type_class_peek_parent(rbx)
if GLIB_VERSION_MAX_ALLOWED GE GLIB_VERSION_2_38
	.if ( &TypeName&_private_offset != 0 )
	    g_type_class_adjust_private_offset(rbx, addr &TypeName&_private_offset)
	.endif
endif
	&type_name&_class_init(rbx)
	ret
    &type_name&_class_intern_init endp
    exitm<>
    endm

_G_DEFINE_TYPE_EXTENDED_BEGIN macro TypeName, type_name, TYPE_PARENT, flags
  local static_g_define_type_id
    &type_name&_init proto :ptr TypeName
    &type_name&_class_init proto :ptr &TypeName&Class
    &type_name&_get_type_once proto
   .data
    align 8
    static_g_define_type_id gsize 0
    &type_name&_parent_class gpointer NULL
    &TypeName&_private_offset gint 0
   .code
    _G_DEFINE_TYPE_EXTENDED_CLASS_INIT(TypeName, type_name)

    &type_name&_get_instance_private proto watcall self:ptr TypeName {
	mov rax,[self].TypeName.&TypeName&_private_offset
	}

    &type_name&_get_type_once proc private uses rbx
	mov rbx,TYPE_PARENT
	mov rdx,g_intern_static_string(@CatStr(<!">, TypeName, <!">))
	.return g_type_register_static_simple(
		rbx,
		rdx,
		sizeof(&TypeName&Class),
		addr &type_name&_class_intern_init,
		sizeof(TypeName),
		addr &type_name&_init,
		flags)
    &type_name&_get_type_once endp

    &type_name&_get_type proc private
	mov static_g_define_type_id,0
	.if g_once_init_enter(addr static_g_define_type_id)
	    g_once_init_leave(addr static_g_define_type_id, &type_name&_get_type_once())
	.endif
	.return static_g_define_type_id
    &type_name&_get_type endp


    exitm<>
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

g_type_get_plugin proto :GType
g_type_interface_get_plugin proto :GType, :GType
g_type_fundamental_next proto
g_type_fundamental proto :GType
g_type_create_instance proto :GType
g_type_free_instance proto :ptr
g_type_add_class_cache_func proto :gpointer, :GTypeClassCacheFunc
g_type_remove_class_cache_func proto :gpointer, :GTypeClassCacheFunc
g_type_class_unref_uncached proto :gpointer
g_type_add_interface_check proto :gpointer, :GTypeInterfaceCheckFunc
g_type_remove_interface_check proto :gpointer, :GTypeInterfaceCheckFunc
g_type_value_table_peek proto :GType

g_type_check_instance proto :ptr
g_type_check_instance_cast proto :ptr, :GType
g_type_check_instance_is_a proto :ptr, :GType
g_type_check_instance_is_fundamentally_a proto :ptr, :GType
g_type_check_class_cast proto :ptr, :GType
g_type_check_class_is_a proto :ptr, :GType
g_type_check_is_value_type proto :GType
g_type_check_value proto :ptr
g_type_check_value_holds proto :ptr, :GType
g_type_test_flags proto :GType, :guint
g_type_name_from_instance proto :ptr
g_type_name_from_class proto :ptr


ifndef G_DISABLE_CAST_CHECKS
_G_TYPE_CIC macro p, g, t
	exitm<g_type_check_instance_cast(p, g)>
	endm
_G_TYPE_CCC macro p, g, t
	exitm<g_type_check_class_cast(p, g)>
	endm
else
_G_TYPE_CIC macro p, g, t
	exitm<p>
	endm
_G_TYPE_CCC macro p, g, t
	exitm<p>
	endm
endif
_G_TYPE_CHI macro ip
	exitm<g_type_check_instance(ip)>
	endm
_G_TYPE_CHV macro vl
	exitm<g_type_check_value(vl)>
	endm
_G_TYPE_IGC proto fastcall ip:ptr GTypeInstance, g:abs, ct:abs {
	mov rax,[ip].GTypeInstance.g_class
	}
_G_TYPE_IGI proto fastcall ip:ptr GTypeInstance, g:abs, ct:abs {
	g_type_interface_peek([ip].GTypeInstance.g_class, g())
	}
_G_TYPE_CIFT macro ip, ft
	exitm<g_type_check_instance_is_fundamentally_a(ip, ft())>
	endm
ifdef __GNUC__
  ;_G_TYPE_CIT(ip, gt) equ (G_GNUC_EXTENSION ({ GTypeInstance *__inst = (GTypeInstance*) ip; GType __t = gt; gboolean __r;   if ( NOT __inst)	    __r = FALSE;   else if (__inst- GT g_class AND __inst- GT g_class- GT g_type EQ __t)     __r = TRUE;   else	    __r = g_type_check_instance_is_a (__inst, __t);   __r; }))
  ;_G_TYPE_CCT(cp, gt) equ (G_GNUC_EXTENSION ({ GTypeClass *__class = (GTypeClass*) cp; GType __t = gt; gboolean __r;	  if ( NOT __class)	__r = FALSE;   else if (__class- GT g_type EQ __t)     __r = TRUE;   else     __r = g_type_check_class_is_a (__class, __t);   __r; }))
  ;_G_TYPE_CVH(vl, gt) equ (G_GNUC_EXTENSION ({ GValue *__val = (GValue*) vl; GType __t = gt; gboolean __r;	if ( NOT __val)	    __r = FALSE;   else if (__val- GT g_type EQ __t)	 __r = TRUE;   else	__r = g_type_check_value_holds (__val, __t);   __r; }))
else
_G_TYPE_CIT macro p, g
	exitm<g_type_check_instance_is_a(p, g)>
	endm
_G_TYPE_CCT macro p, g
	exitm<g_type_check_class_is_a(p, g)>
	endm
_G_TYPE_CVH macro vl, g
	exitm<g_type_check_value_holds(vl, g)>
	endm
endif

define G_TYPE_FLAG_RESERVED_ID_BIT (1 shl 0)

endif

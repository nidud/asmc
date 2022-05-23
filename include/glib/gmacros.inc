ifndef __G_MACROS_H__
define __G_MACROS_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stddef.inc

G_ASMC_CHECK_VERSION macro major, minor
ifdef __ASMC__
 if ((__ASMC__ gt (major)) or ((__ASMC__ eq (major)) and ((__ASMC__ mod 100) ge (minor))))
    exitm<1>
 else
    exitm<0>
 endif
else
    exitm<0>
endif
    endm

g_macro__has_attribute macro x
    exitm<g_macro__has_attribute_&x&>
    endm

define g_macro__has_attribute___pure__                      0 ; G_GNUC_CHECK_VERSION (2, 96)
define g_macro__has_attribute___malloc__                    0 ; G_GNUC_CHECK_VERSION (2, 96)
define g_macro__has_attribute___noinline__                  0 ; G_GNUC_CHECK_VERSION (2, 96)
define g_macro__has_attribute___sentinel__                  0 ; G_GNUC_CHECK_VERSION (4, 0)
define g_macro__has_attribute___alloc_size__                0 ; G_GNUC_CHECK_VERSION (4, 3)
define g_macro__has_attribute___format__                    0 ; G_GNUC_CHECK_VERSION (2, 4)
define g_macro__has_attribute___format_arg__                0 ; G_GNUC_CHECK_VERSION (2, 4)
define g_macro__has_attribute___noreturn__                  0 ; (G_GNUC_CHECK_VERSION (2, 8) || (0x5110 <= __SUNPRO_C))
define g_macro__has_attribute___const__                     0 ; G_GNUC_CHECK_VERSION (2, 4)
define g_macro__has_attribute___unused__                    0 ; G_GNUC_CHECK_VERSION (2, 4)
define g_macro__has_attribute___no_instrument_function__    0 ; G_GNUC_CHECK_VERSION (2, 4)
define g_macro__has_attribute_fallthrough                   1 ; G_GNUC_CHECK_VERSION (6, 0)
define g_macro__has_attribute___deprecated__                0 ; G_GNUC_CHECK_VERSION (3, 1)
define g_macro__has_attribute_may_alias                     0 ; G_GNUC_CHECK_VERSION (3, 3)
define g_macro__has_attribute_warn_unused_result            0 ; G_GNUC_CHECK_VERSION (3, 4)
define g_macro__has_attribute_cleanup                       0;1 ; G_GNUC_CHECK_VERSION (3, 3)

ifndef __GI_SCANNER__

if g_macro__has_attribute(cleanup)

_GLIB_AUTOPTR_FUNC_NAME macro TypeName
    exitm<glib_autoptr_cleanup_&TypeName&>
    endm
_GLIB_AUTOPTR_CLEAR_FUNC_NAME macro TypeName
    exitm<glib_autoptr_clear_&TypeName&>
    endm
_GLIB_AUTOPTR_TYPENAME macro TypeName
    exitm<&TypeName&_autoptr>
    endm
_GLIB_AUTOPTR_LIST_FUNC_NAME macro TypeName
    exitm<glib_listautoptr_cleanup_&TypeName&>
    endm
_GLIB_AUTOPTR_LIST_TYPENAME macro TypeName
    exitm<&TypeName&_listautoptr>
    endm
_GLIB_AUTOPTR_SLIST_FUNC_NAME macro TypeName
    exitm<glib_slistautoptr_cleanup_&TypeName&>
    endm
_GLIB_AUTOPTR_SLIST_TYPENAME macro TypeName
    exitm<&TypeName&_slistautoptr>
    endm
_GLIB_AUTOPTR_QUEUE_FUNC_NAME macro TypeName
    exitm<glib_queueautoptr_cleanup_&TypeName&>
    endm
_GLIB_AUTOPTR_QUEUE_TYPENAME macro TypeName
    exitm<&TypeName&_queueautoptr>
    endm
_GLIB_AUTO_FUNC_NAME macro TypeName
    exitm<glib_auto_cleanup_&TypeName&>
    endm
_GLIB_CLEANUP macro func
    exitm<func>
    endm

_GLIB_DEFINE_AUTOPTR_CLEANUP_FUNCS macro TypeName, ParentName, cleanup

  local clear,queue

    _GLIB_AUTOPTR_TYPENAME(TypeName)        typedef ptr TypeName
    _GLIB_AUTOPTR_LIST_TYPENAME(TypeName)   typedef ptr GList
    _GLIB_AUTOPTR_SLIST_TYPENAME(TypeName)  typedef ptr GSList
    _GLIB_AUTOPTR_QUEUE_TYPENAME(TypeName)  typedef ptr GQueue

    clear textequ _GLIB_AUTOPTR_CLEAR_FUNC_NAME(TypeName)
    queue textequ _GLIB_AUTOPTR_QUEUE_FUNC_NAME(TypeName)

    clear proto fastcall _ptr:ptr TypeName {
        .if (_ptr)
            cleanup(_ptr)
        .endif
        }
    _GLIB_AUTOPTR_FUNC_NAME(TypeName) proto fastcall _ptr:ptr ptr TypeName {
        clear([_ptr])
        }
    _GLIB_AUTOPTR_LIST_FUNC_NAME(TypeName) proto fastcall _l:ptr ptr GList {
        g_list_free_full([_l], addr cleanup)
        }
    _GLIB_AUTOPTR_SLIST_FUNC_NAME(TypeName) proto fastcall _l:ptr ptr GSList {
        g_slist_free_full([_l], addr cleanup)
        }
    queue proto fastcall _q:ptr ptr GQueue {
        mov rcx,[_q]
        .if ( rcx )
            g_queue_free_full(rcx, addr cleanup)
        .endif
        }
    exitm<>
    endm

_GLIB_DEFINE_AUTOPTR_CHAINUP macro ModuleObjName, ParentName
    exitm<_GLIB_DEFINE_AUTOPTR_CLEANUP_FUNCS(ModuleObjName, ParentName, _GLIB_AUTOPTR_CLEAR_FUNC_NAME(ParentName))>
    endm
G_DEFINE_AUTOPTR_CLEANUP_FUNC macro TypeName, func
    exitm<_GLIB_DEFINE_AUTOPTR_CLEANUP_FUNCS(TypeName, TypeName, func)>
    endm
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC macro TypeName, func
    _GLIB_AUTO_FUNC_NAME(TypeName) proto _ptr:ptr TypeName {
        func(_ptr)
        }
    exitm<>
    endm

G_DEFINE_AUTO_CLEANUP_FREE_FUNC macro TypeName, func, none
    local name
    name textequ _GLIB_AUTO_FUNC_NAME(TypeName)
    name proto fastcall _ptr:ptr TypeName {
        mov rcx,[_ptr]
        .if ( rcx != none )
            func(rcx)
        .endif
        }
    exitm<>
    endm

g_autoptr macro TypeName
    exitm<_GLIB_CLEANUP(_GLIB_AUTOPTR_FUNC_NAME(TypeName))(_GLIB_AUTOPTR_TYPENAME(TypeName))>
    endm
g_autolist macro TypeName
    exitm<_GLIB_CLEANUP(_GLIB_AUTOPTR_LIST_FUNC_NAME(TypeName))(_GLIB_AUTOPTR_LIST_TYPENAME(TypeName))>
    endm
g_autoslist macro TypeName
    exitm<_GLIB_CLEANUP(_GLIB_AUTOPTR_SLIST_FUNC_NAME(TypeName))(_GLIB_AUTOPTR_SLIST_TYPENAME(TypeName))>
    endm
g_autoqueue macro TypeName
    exitm<_GLIB_CLEANUP(_GLIB_AUTOPTR_QUEUE_FUNC_NAME(TypeName))(_GLIB_AUTOPTR_QUEUE_TYPENAME(TypeName))>
    endm
g_auto macro TypeName
    exitm<_GLIB_CLEANUP(_GLIB_AUTO_FUNC_NAME(TypeName))(TypeName)>
    endm
g_autofree macro
    exitm<_GLIB_CLEANUP(g_autoptr_cleanup_generic_gfree)>
    endm

else

_GLIB_DEFINE_AUTOPTR_CHAINUP macro ModuleObjName, ParentName
    exitm<>
    endm
G_DEFINE_AUTOPTR_CLEANUP_FUNC macro TypeName, func
    exitm<>
    endm
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC macro TypeName, func
    exitm<>
    endm
G_DEFINE_AUTO_CLEANUP_FREE_FUNC macro TypeName, func, none
    exitm<>
    endm
endif

else

_GLIB_DEFINE_AUTOPTR_CHAINUP macro ModuleObjName, ParentName
    exitm<>
    endm
G_DEFINE_AUTOPTR_CLEANUP_FUNC macro TypeName, func
    exitm<>
    endm
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC macro TypeName, func
    exitm<>
    endm
G_DEFINE_AUTO_CLEANUP_FREE_FUNC macro TypeName, func, none
    exitm<>
    endm

endif
G_N_ELEMENTS macro arr
    exitm<lengthof(arr)>
    endm
endif

ifndef __G_MACROS_H__
__G_MACROS_H__ equ <>
if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include stddef.inc

G_GNUC_CHECK_VERSION macro major, minor
	exitm<.err>
	endm

G_GNUC_EXTENSION equ 1

G_CAN_INLINE equ 1

ifndef __cplusplus
 ifdef _MSC_VER
  if (_MSC_VER LT 1900)
   G_INLINE_DEFINE_NEEDED equ 1
  endif
 elseif NOT defined(__STDC_VERSION__) OR (__STDC_VERSION__ LT 199900)
  G_INLINE_DEFINE_NEEDED equ 1
 endif
endif

ifdef G_INLINE_DEFINE_NEEDED
 ;undef inline
 ;define inline __inline
endif

;undef G_INLINE_DEFINE_NEEDED

ifdef G_IMPLEMENT_INLINES
  ;define G_INLINE_FUNC extern
  ;undef  G_CAN_INLINE
else
  ;define G_INLINE_FUNC static inline
endif

G_GNUC_PURE		equ 1
G_GNUC_MALLOC		equ 1
G_GNUC_NULL_TERMINATED	equ 1

ifndef __has_attribute
__has_attribute macro x
	exitm<0>
	endm
endif

ifndef __has_feature
__has_feature macro x
	exitm<0>
	endm
endif

ifndef __has_builtin
__has_builtin macro x
	exitm<0>
	endm
endif

G_GNUC_ALLOC_SIZE macro x
	exitm<1>
	endm
G_GNUC_ALLOC_SIZE2 macro x,y
	exitm<1>
	endm

G_GNUC_PRINTF macro format_idx, arg_idx
	exitm<>
	endm
G_GNUC_SCANF macro format_idx, arg_idx
	exitm<>
	endm
G_GNUC_FORMAT macro arg_idx
	exitm<>
	endm
G_GNUC_NORETURN		equ 1
G_GNUC_CONST		equ 1
G_GNUC_UNUSED		equ 1
G_GNUC_NO_INSTRUMENT	equ 1
G_GNUC_DEPRECATED	equ 1

G_GNUC_DEPRECATED_FOR macro f
	exitm<G_GNUC_DEPRECATED>
	endm

G_GNUC_BEGIN_IGNORE_DEPRECATIONS equ 1
G_GNUC_END_IGNORE_DEPRECATIONS equ 1
G_GNUC_MAY_ALIAS equ 1
G_GNUC_WARN_UNUSED_RESULT equ 1

ifndef G_DISABLE_DEPRECATED
G_GNUC_FUNCTION		equ <"">
G_GNUC_PRETTY_FUNCTION	equ <"">
endif

G_ANALYZER_ANALYZING	equ 0
G_ANALYZER_NORETURN	equ 1

G_STRINGIFY macro macro_or_string
	exitm<G_STRINGIFY_ARG (macro_or_string)>
	endm
G_STRINGIFY_ARG macro contents
	exitm<#contents>
	endm

ifndef __GI_SCANNER__
G_PASTE_ARGS macro identifier1,identifier2
	exitm<identifier1&identifier2&>
	endm
G_PASTE macro identifier1,identifier2
	exitm<G_PASTE_ARGS (identifier1, identifier2)>
	endm
ifdef __COUNTER__
G_STATIC_ASSERT macro expr
	exitm<-1>
	endm
else
G_STATIC_ASSERT macro expr
	exitm<-1>
	endm
endif
G_STATIC_ASSERT_EXPR macro expr
	exitm<-1>
	endm
endif

;G_STRLOC		 equ __FILE__ ":" G_STRINGIFY (__LINE__)

G_BEGIN_DECLS		equ <>
G_END_DECLS		equ <>

ifndef NULL
NULL			equ 0
endif
ifndef FALSE
FALSE			equ 0
endif
ifndef TRUE
TRUE			equ 1
endif

if 0
undef	MAX
MAX macro a, b
	exitm<(((a) GT (b)) ? (a) : (b))>
	endm

undef	MIN
MIN macro a, b
	exitm<(((a) LT (b)) ? (a) : (b))>
	endm

undef	ABS
ABS macro a
	exitm<(((a) LT 0) ? -(a) : (a))>
	endm

undef	CLAMP
CLAMP macro x, low, high
	exitm<(((x) GT (high)) ? (high) : (((x) LT (low)) ? (low) : (x)))>
	endm
endif
G_N_ELEMENTS macro arr
	exitm<lengthof(arr)>
	endm

GPOINTER_TO_SIZE macro p
	exitm<(p)>
	endm
GSIZE_TO_POINTER macro s
	exitm<(s)>
	endm

G_STRUCT_OFFSET macro struct_type, member
	exitm<.err>
	endm

G_STRUCT_MEMBER_P macro struct_p, struct_offset
	exitm<.err>
	endm
G_STRUCT_MEMBER macro member_type, struct_p, struct_offset
	exitm<.err>
	endm

if NOT (defined (G_STMT_START) AND defined (G_STMT_END))
G_STMT_START equ <.repeat>
G_STMT_END   equ <.until 1>
endif

ifndef G_DISABLE_DEPRECATED
G_CONST_RETURN equ <>
endif

G_LIKELY macro expr
	exitm<(expr)>
	endm
G_UNLIKELY macro expr
	exitm<(expr)>
	endm

G_DEPRECATED equ 1
G_DEPRECATED_FOR macro f
	exitm<G_DEPRECATED>
	endm

G_UNAVAILABLE macro maj,min
	exitm<G_DEPRECATED>
	endm

ifndef _GLIB_EXTERN
_GLIB_EXTERN		equ extern
endif


ifdef GLIB_DISABLE_DEPRECATION_WARNINGS
GLIB_DEPRECATED equ _GLIB_EXTERN
GLIB_DEPRECATED_FOR macro f
	exitm<_GLIB_EXTERN>
	endm
GLIB_UNAVAILABLE macro maj,min
	exitm<_GLIB_EXTERN>
	endm
else
GLIB_DEPRECATED equ G_DEPRECATED _GLIB_EXTERN
GLIB_DEPRECATED_FOR macro f
	exitm<G_DEPRECATED_FOR(f) _GLIB_EXTERN>
	endm
GLIB_UNAVAILABLE macro maj,min
	exitm<G_UNAVAILABLE(maj,min) _GLIB_EXTERN>
	endm
endif

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

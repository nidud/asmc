ifndef __G_BOXED_H__
__G_BOXED_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc
ifndef __GI_SCANNER__
include gobject/glib-types.inc
endif

G_TYPE_IS_BOXED macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_BOXED)>
	endm
G_VALUE_HOLDS_BOXED macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_BOXED))>
	endm


CALLBACKC(GBoxedCopyFunc, :gpointer)
CALLBACKC(GBoxedFreeFunc, :gpointer)


;gpointer
g_boxed_copy proto __cdecl \
	    boxed_type: GType,
	     src_boxed: gconstpointer

g_boxed_free proto __cdecl \
	    boxed_type: GType,
		 boxed: gpointer

g_value_set_boxed proto __cdecl \
		 value: ptr GValue,
	       v_boxed: gconstpointer

g_value_set_static_boxed proto __cdecl \
		 value: ptr GValue,
	       v_boxed: gconstpointer

g_value_take_boxed proto __cdecl \
		 value: ptr GValue,
	       v_boxed: gconstpointer

g_value_set_boxed_take_ownership proto __cdecl \
		 value: ptr GValue,
	       v_boxed: gconstpointer

;gpointer
g_value_get_boxed proto __cdecl \
		 value: ptr GValue

;gpointer
g_value_dup_boxed proto __cdecl \
		 value: ptr GValue

;GType
g_boxed_type_register_static proto __cdecl \
		  name: ptr gchar,
	    boxed_copy: GBoxedCopyFunc,
	    boxed_free: GBoxedFreeFunc


G_TYPE_CLOSURE		equ <g_closure_get_type>
G_TYPE_VALUE		equ <g_value_get_type>

g_closure_get_type	proto __cdecl
g_value_get_type	proto __cdecl

endif

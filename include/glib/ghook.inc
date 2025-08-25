ifndef __G_HOOK_H__
define __G_HOOK_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc

CALLBACKC(GHookCompareFunc, :ptr, :ptr)
CALLBACKC(GHookFindFunc, :ptr, :gpointer)
CALLBACKC(GHookMarshaller, :ptr, :gpointer)
CALLBACKC(GHookCheckMarshaller, :ptr, :gpointer)
CALLBACKC(GHookFunc, :gpointer)
CALLBACKC(GHookCheckFunc, :gpointer)
CALLBACKC(GHookFinalizeFunc, :ptr, :ptr)

.enum GHookFlagMask {
    G_HOOK_FLAG_ACTIVE	    = 1 shl 0,
    G_HOOK_FLAG_IN_CALL	    = 1 shl 1,
    G_HOOK_FLAG_MASK	    = 0x0f
    }

G_HOOK_FLAG_USER_SHIFT	equ (4)

GHookList		STRUC
seq_id			gulong ?
RECORD
hook_size		guint : 16 ?
is_setup		guint : 1 ?
ENDS
hooks			ptr GHook ?
dummy3			gpointer ?
finalize_hook		GHookFinalizeFunc ?
dummy			gpointer 2 dup(?)
GHookList		ENDS

GHook			STRUC
data			gpointer ?
next			ptr GHook ?
prev			ptr GHook ?
ref_count		guint ?
hook_id			gulong ?
flags			guint ?
func			gpointer ?
destroy			GDestroyNotify ?
GHook			ENDS


g_hook_list_init proto __cdecl :ptr, :guint
g_hook_list_clear proto __cdecl :ptr
g_hook_alloc proto __cdecl :ptr
g_hook_free proto __cdecl :ptr, :ptr
g_hook_ref proto __cdecl :ptr, :ptr
g_hook_unref proto __cdecl :ptr, :ptr
g_hook_destroy proto __cdecl :ptr, :gulong
g_hook_destroy_link proto __cdecl :ptr, :ptr
g_hook_prepend proto __cdecl :ptr, :ptr
g_hook_insert_before proto __cdecl :ptr, :ptr, :ptr
g_hook_insert_sorted proto __cdecl :ptr, :ptr, :GHookCompareFunc
g_hook_get proto __cdecl :ptr, :gulong
g_hook_find proto __cdecl :ptr, :gboolean, :GHookFindFunc, :gpointer
g_hook_find_data proto __cdecl :ptr, :gboolean, :gpointer
g_hook_find_func proto __cdecl :ptr, :gboolean, :gpointer
g_hook_find_func_data proto __cdecl :ptr, :gboolean, :gpointer, :gpointer

g_hook_first_valid proto __cdecl :ptr, :gboolean
g_hook_next_valid proto __cdecl :ptr, :ptr, :gboolean
g_hook_compare_ids proto __cdecl :ptr, :ptr
g_hook_list_invoke proto __cdecl :ptr, :gboolean
g_hook_list_invoke_check proto __cdecl :ptr, :gboolean
g_hook_list_marshal proto __cdecl :ptr, :gboolean, :GHookMarshaller, :gpointer
g_hook_list_marshal_check proto __cdecl :ptr, :gboolean, :GHookCheckMarshaller, :gpointer

endif

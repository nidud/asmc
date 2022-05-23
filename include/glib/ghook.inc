ifndef __G_HOOK_H__
define __G_HOOK_H__

if NOT defined (__GLIB_H_INSIDE__) AND NOT defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gmem.inc

CALLBACKC(GHookCompareFunc, :ptr GHook, :ptr GHook)
CALLBACKC(GHookFindFunc, :ptr GHook, :gpointer)
CALLBACKC(GHookMarshaller, :ptr GHook, :gpointer)
CALLBACKC(GHookCheckMarshaller, :ptr GHook, :gpointer)
CALLBACKC(GHookFunc, :gpointer)
CALLBACKC(GHookCheckFunc, :gpointer)
CALLBACKC(GHookFinalizeFunc, :ptr GHookList, :ptr GHook)

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



G_HOOK macro hook
	exitm<.err>
	endm
G_HOOK_FLAGS macro hook
	exitm<.err>
	endm
G_HOOK_ACTIVE macro hook
	exitm<.err>
	endm

G_HOOK_IN_CALL macro hook
	exitm<.err>
	endm

G_HOOK_IS_VALID macro hook
	exitm<.err>
	endm
G_HOOK_IS_UNLINKED macro hook
	exitm<.err>
	endm

;void
g_hook_list_init proto __cdecl \
	     hook_list: ptr GHookList,
	     hook_size: guint

;void
g_hook_list_clear proto __cdecl \
	     hook_list: ptr GHookList

;GHook*
g_hook_alloc proto __cdecl \
	     hook_list: ptr GHookList

;void
g_hook_free proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook

;GHook
g_hook_ref proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook

;void
g_hook_unref proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook

;gboolean
g_hook_destroy proto __cdecl \
	     hook_list: ptr GHookList,
	       hook_id: gulong

;void
g_hook_destroy_link proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook

;void
g_hook_prepend proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook

;void
g_hook_insert_before proto __cdecl \
	     hook_list: ptr GHookList,
	       sibling: ptr GHook,
		  hook: ptr GHook

;void
g_hook_insert_sorted proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook,
		  func: GHookCompareFunc

;GHook*
g_hook_get proto __cdecl \
	     hook_list: ptr GHookList,
	       hook_id: gulong

;GHook*
g_hook_find proto __cdecl \
	     hook_list: ptr GHookList,
	   need_valids: gboolean,
		  func: GHookFindFunc,
		  data: gpointer

;GHook*
g_hook_find_data proto __cdecl \
	     hook_list: ptr GHookList,
	   need_valids: gboolean,
		  data: gpointer

;GHook*
g_hook_find_func proto __cdecl \
	     hook_list: ptr GHookList,
	   need_valids: gboolean,
		  func: gpointer

;GHook*
g_hook_find_func_data proto __cdecl \
	     hook_list: ptr GHookList,
	   need_valids: gboolean,
		  func: gpointer,
		  data: gpointer


;GHook*
g_hook_first_valid proto __cdecl \
	     hook_list: ptr GHookList,
	may_be_in_call: gboolean

;GHook*
g_hook_next_valid proto __cdecl \
	     hook_list: ptr GHookList,
		  hook: ptr GHook,
	may_be_in_call: gboolean


;gint
g_hook_compare_ids proto __cdecl \
	      new_hook: ptr GHook,
	       sibling: ptr GHook


g_hook_append macro hook_list, hook
	exitm<.err>
	endm

;void
g_hook_list_invoke proto __cdecl \
	     hook_list: ptr GHookList,
	   may_recurse: gboolean

;void
g_hook_list_invoke_check proto __cdecl \
	     hook_list: ptr GHookList,
	   may_recurse: gboolean

;void
g_hook_list_marshal proto __cdecl \
	     hook_list: ptr GHookList,
	   may_recurse: gboolean,
	    marshaller: GHookMarshaller,
	  marshal_data: gpointer

;void
g_hook_list_marshal_check proto __cdecl \
	     hook_list: ptr GHookList,
	   may_recurse: gboolean,
	    marshaller: GHookCheckMarshaller,
	  marshal_data: gpointer


endif

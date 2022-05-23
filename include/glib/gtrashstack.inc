ifndef __G_TRASH_STACK_H__
define __G_TRASH_STACK_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gutils.inc

_GTrashStack            struct
next                    ptr GTrashStack ?
_GTrashStack            ends
GTrashStack             typedef _GTrashStack

g_trash_stack_push proto :ptr, :gpointer
g_trash_stack_pop proto :ptr
g_trash_stack_peek proto :ptr
g_trash_stack_height proto :ptr

endif

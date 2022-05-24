ifndef __G_CLOSURE_H__
define __G_CLOSURE_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_CLOSURE_NEEDS_MARSHAL macro closure
  exitm<(( (closure)).marshal eq NULL)>
  endm

G_CLOSURE_N_NOTIFIERS macro l
  exitm<(((l).n_guards shl 1) + (l).n_fnotifiers + (l).n_inotifiers)>
  endm

G_CCLOSURE_SWAP_DATA macro cclosure
  exitm<(( (cclosure)).derivative_flag)>
  endm

G_CALLBACK macro f
  exitm<addr f>
  endm


CALLBACK(GCallback,)
CALLBACK(GClosureNotify, :gpointer, :ptr)
CALLBACK(GClosureMarshal, :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer)
CALLBACK(GVaClosureMarshal, :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr)

_GClosureNotifyData     struct
data                    gpointer ?
notify                  GClosureNotify ?
_GClosureNotifyData     ends
GClosureNotifyData      typedef _GClosureNotifyData

_GClosure               struct
RECORD
ref_count               guint : 15 ?
meta_marshal_nouse      guint :  1 ?
n_guards                guint :  1 ?
n_fnotifiers            guint :  2 ?
n_inotifiers            guint :  8 ?
in_inotify              guint :  1 ?
floating                guint :  1 ?
derivative_flag         guint :  1 ?
in_marshal              guint :  1 ?
is_invalid              guint :  1 ?
ENDS
marshal                 proc :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
data                    gpointer ?
notifiers               ptr GClosureNotifyData ?
_GClosure               ends
GClosure                typedef _GClosure

_GCClosure              struct
closure                 GClosure <>
callback                gpointer ?
_GCClosure              ends
GCClosure               typedef _GCClosure

g_cclosure_new proto :GCallback, :gpointer, :GClosureNotify
g_cclosure_new_swap proto :GCallback, :gpointer, :GClosureNotify
g_signal_type_cclosure_new proto :GType, :guint

g_closure_ref proto :ptr
g_closure_sink proto :ptr
g_closure_unref proto :ptr

g_closure_new_simple proto :guint, :gpointer
g_closure_add_finalize_notifier proto :ptr, :gpointer, :GClosureNotify
g_closure_remove_finalize_notifier proto :ptr, :gpointer, :GClosureNotify
g_closure_add_invalidate_notifier proto :ptr, :gpointer, :GClosureNotify
g_closure_remove_invalidate_notifier proto :ptr, :gpointer, :GClosureNotify
g_closure_add_marshal_guards proto :ptr, :gpointer, :GClosureNotify, :gpointer, :GClosureNotify
g_closure_set_marshal proto :ptr, :GClosureMarshal
g_closure_set_meta_marshal proto :ptr, :gpointer, :GClosureMarshal
g_closure_invalidate proto :ptr
g_closure_invoke proto :ptr, :ptr, :guint, :ptr, :gpointer

g_cclosure_marshal_generic proto :ptr, :ptr, :guint, :ptr, :gpointer, :gpointer
g_cclosure_marshal_generic_va proto :ptr, :ptr, :gpointer, :va_list, :gpointer, :sdword, :ptr

endif

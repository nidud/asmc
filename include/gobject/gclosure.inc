ifndef __G_CLOSURE_H__
__G_CLOSURE_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_CLOSURE_NEEDS_MARSHAL macro closure
	exitm<(closure.marshal == NULL)>
	endm
G_CLOSURE_N_NOTIFIERS macro l
	exitm<.err>
	endm

G_CCLOSURE_SWAP_DATA macro cclosure
	exitm<.err>
	endm

G_CALLBACK macro f
	exitm<.err>
	endm

CALLBACKC(GCallback)
CALLBACKC(GClosureNotify, :gpointer, :ptr GClosure)
CALLBACKC(GClosureMarshal, :ptr GClosure, :ptr GValue, :guint, :ptr GValue, :gpointer, :gpointer)
CALLBACKC(GVaClosureMarshal, :ptr GClosure, :ptr GValue, :gpointer, :va_list, :gpointer, :int_t, :ptr GType)


GClosureNotifyData	STRUC
data			gpointer ?
notify			GClosureNotify ?
GClosureNotifyData	ENDS

GClosure		STRUC
ref_count		guint ?
;ref_count : 15
;meta_marshal_nouse : 1
;n_guards : 1
;n_fnotifiers : 2
;n_inotifiers : 8
;in_inotify : 1
;floating : 1
;derivative_flag : 1
;in_marshal : 1
;is_invalid : 1
marshal			proc :ptr GClosure, :ptr GValue, :guint, :ptr GValue, :gpointer, :gpointer
GClosure		ENDS

GCClosure		STRUC
closure			GClosure <>
callback		gpointer ?
GCClosure		ENDS

;GClosure*
g_cclosure_new proto __cdecl \
	 callback_func: GCallback,
	     user_data: gpointer,
	  destroy_data: GClosureNotify

g_cclosure_new_swap proto __cdecl \
	 callback_func: GCallback,
	     user_data: gpointer,
	  destroy_data: GClosureNotify

g_signal_type_cclosure_new proto __cdecl \
		 itype: GType,
	 struct_offset: guint


g_closure_ref proto __cdecl \
	       closure: ptr GClosure

g_closure_sink proto __cdecl \
	       closure: ptr GClosure

g_closure_unref proto __cdecl \
	       closure: ptr GClosure

g_closure_new_simple proto __cdecl \
	sizeof_closure: guint,
		  data: gpointer

g_closure_add_finalize_notifier proto __cdecl \
	       closure: ptr GClosure,
	   notify_data: gpointer,
	   notify_func: GClosureNotify

g_closure_remove_finalize_notifier proto __cdecl \
	       closure: ptr GClosure,
	   notify_data: gpointer,
	   notify_func: GClosureNotify

g_closure_add_invalidate_notifier proto __cdecl \
	       closure: ptr GClosure,
	   notify_data: gpointer,
	   notify_func: GClosureNotify

g_closure_remove_invalidate_notifier proto __cdecl \
	       closure: ptr GClosure,
	   notify_data: gpointer,
	   notify_func: GClosureNotify

g_closure_add_marshal_guards proto __cdecl \
	       closure: ptr GClosure,
      pre_marshal_data: gpointer,
    pre_marshal_notify: GClosureNotify,
     post_marshal_data: gpointer,
   post_marshal_notify: GClosureNotify

g_closure_set_marshal proto __cdecl \
	       closure: ptr GClosure,
	       marshal: GClosureMarshal

g_closure_set_meta_marshal proto __cdecl \
	       closure: ptr GClosure,
	  marshal_data: gpointer,
	  meta_marshal: GClosureMarshal

g_closure_invalidate proto __cdecl \
	       closure: ptr GClosure

g_closure_invoke proto __cdecl \
	       closure: ptr GClosure,
	  return_value: ptr GValue,
	n_param_values: guint,
	  param_values: ptr GValue,
       invocation_hint: gpointer

g_cclosure_marshal_generic proto __cdecl \
	       closure: ptr GClosure,
	 return_gvalue: ptr GValue,
	n_param_values: guint,
	  param_values: ptr GValue,
       invocation_hint: gpointer,
	  marshal_data: gpointer


g_cclosure_marshal_generic_va proto __cdecl \
	       closure: ptr GClosure,
	  return_value: ptr GValue,
	      instance: gpointer,
	     args_list: va_list,
	  marshal_data: gpointer,
	      n_params: int_t,
	   param_types: ptr GType

endif

ifndef __G_SIGNAL_H__
__G_SIGNAL_H__ equ <>
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gclosure.inc
include gobject/gvalue.inc
include gobject/gparam.inc
include gobject/gmarshal.inc

GSignalCMarshaller	typedef GClosureMarshal
GSignalCVaMarshaller	typedef GVaClosureMarshal

CALLBACKC(GSignalEmissionHook, :ptr GSignalInvocationHint, :guint, :ptr GValue, :gpointer)
CALLBACKC(GSignalAccumulator, :ptr GSignalInvocationHint, :ptr GValue, :ptr GValue, :gpointer)

.enum GSignalFlags {
    G_SIGNAL_RUN_FIRST	= 1 shl 0,
    G_SIGNAL_RUN_LAST	= 1 shl 1,
    G_SIGNAL_RUN_CLEANUP= 1 shl 2,
    G_SIGNAL_NO_RECURSE = 1 shl 3,
    G_SIGNAL_DETAILED	= 1 shl 4,
    G_SIGNAL_ACTION	= 1 shl 5,
    G_SIGNAL_NO_HOOKS	= 1 shl 6,
    G_SIGNAL_MUST_COLLECT= 1 shl 7,
    G_SIGNAL_DEPRECATED = 1 shl 8
}

G_SIGNAL_FLAGS_MASK	equ 0x1ff

.enum GConnectFlags {
    G_CONNECT_AFTER	= 1 shl 0,
    G_CONNECT_SWAPPED	= 1 shl 1
}

.enum GSignalMatchType {
    G_SIGNAL_MATCH_ID	= 1 shl 0,
    G_SIGNAL_MATCH_DETAIL = 1 shl 1,
    G_SIGNAL_MATCH_CLOSURE = 1 shl 2,
    G_SIGNAL_MATCH_FUNC = 1 shl 3,
    G_SIGNAL_MATCH_DATA = 1 shl 4,
    G_SIGNAL_MATCH_UNBLOCKED = 1 shl 5
}

G_SIGNAL_MATCH_MASK	equ 0x3f
G_SIGNAL_TYPE_STATIC_SCOPE equ G_TYPE_FLAG_RESERVED_ID_BIT

GSignalInvocationHint	STRUC
signal_id		guint ?
detail			GQuark ?
run_type		GSignalFlags ?
GSignalInvocationHint	ENDS

GSignalQuery		STRUC
signal_id		guint ?
signal_name		string_t ?
itype			GType ?
signal_flags		GSignalFlags ?
return_type		GType ?
n_params		guint ?
param_types		ptr_t ?
GSignalQuery		ENDS


;guint
g_signal_newv proto __cdecl \
	   signal_name: ptr gchar,
		 itype: GType,
	  signal_flags: GSignalFlags,
	 class_closure: ptr GClosure,
	   accumulator: GSignalAccumulator,
	     accu_data: gpointer,
	  c_marshaller: GSignalCMarshaller,
	   return_type: GType,
	      n_params: guint,
	   param_types: ptr GType

;guint
g_signal_new_valist proto __cdecl \
	   signal_name: ptr gchar,
		 itype: GType,
	  signal_flags: GSignalFlags,
	 class_closure: ptr GClosure,
	   accumulator: GSignalAccumulator,
	     accu_data: gpointer,
	  c_marshaller: GSignalCMarshaller,
	   return_type: GType,
	      n_params: guint,
		  args: va_list

;guint
g_signal_new proto _CDecl \
	   signal_name: ptr gchar,
		 itype: GType,
	  signal_flags: GSignalFlags,
	  class_offset: guint,
	   accumulator: GSignalAccumulator,
	     accu_data: gpointer,
	  c_marshaller: GSignalCMarshaller,
	   return_type: GType,
	      n_params: guint,
		      : vararg

;guint
g_signal_new_class_handler proto _CDecl \
	   signal_name: ptr gchar,
		 itype: GType,
	  signal_flags: GSignalFlags,
	 class_handler: GCallback,
	   accumulator: GSignalAccumulator,
	     accu_data: gpointer,
	  c_marshaller: GSignalCMarshaller,
	   return_type: GType,
	      n_params: guint,
		      : vararg

g_signal_set_va_marshaller proto __cdecl \
	     signal_id: guint,
	 instance_type: GType,
	 va_marshaller: GSignalCVaMarshaller

g_signal_emitv proto __cdecl \
   instance_and_params: ptr GValue,
	     signal_id: guint,
		detail: GQuark,
	  return_value: ptr GValue

g_signal_emit_valist proto __cdecl \
	      instance: gpointer,
	     signal_id: guint,
		detail: GQuark,
	      var_args: va_list

g_signal_emit proto _CDecl \
	      instance: gpointer,
	     signal_id: guint,
		detail: GQuark,
		      : vararg

g_signal_emit_by_name proto _CDecl \
	      instance: gpointer,
       detailed_signal: ptr gchar,
		      : vararg

;guint
g_signal_lookup proto __cdecl \
		  name: ptr gchar,
		 itype: GType

;const
g_signal_name proto __cdecl \
	     signal_id: guint

g_signal_query proto __cdecl \
	     signal_id: guint,
		 query: ptr GSignalQuery

;guint*
g_signal_list_ids proto __cdecl \
		 itype: GType,
		 n_ids: ptr guint

;gboolean
g_signal_parse_name proto __cdecl \
       detailed_signal: ptr gchar,
		 itype: GType,
	   signal_id_p: ptr guint,
	      detail_p: ptr GQuark,
    force_detail_quark: gboolean

;GSignalInvocationHint*
g_signal_get_invocation_hint proto __cdecl \
	      instance: gpointer

g_signal_stop_emission proto __cdecl \
	      instance: gpointer,
	     signal_id: guint,
		detail: GQuark

g_signal_stop_emission_by_name proto __cdecl \
	      instance: gpointer,
       detailed_signal: ptr gchar

;gulong
g_signal_add_emission_hook proto __cdecl \
	     signal_id: guint,
		detail: GQuark,
	     hook_func: GSignalEmissionHook,
	     hook_data: gpointer,
	  data_destroy: GDestroyNotify

g_signal_remove_emission_hook proto __cdecl \
	     signal_id: guint,
	       hook_id: gulong

;gboolean
g_signal_has_handler_pending proto __cdecl \
	      instance: gpointer,
	     signal_id: guint,
		detail: GQuark,
	may_be_blocked: gboolean

;gulong
g_signal_connect_closure_by_id proto __cdecl \
	      instance: gpointer,
	     signal_id: guint,
		detail: GQuark,
	       closure: ptr GClosure,
		 after: gboolean

;gulong
g_signal_connect_closure proto __cdecl \
	      instance: gpointer,
       detailed_signal: ptr gchar,
	       closure: ptr GClosure,
		 after: gboolean

;gulong
g_signal_connect_data proto __cdecl \
	      instance: gpointer,
       detailed_signal: ptr gchar,
	     c_handler: GCallback,
		  data: gpointer,
	  destroy_data: GClosureNotify,
	 connect_flags: GConnectFlags

g_signal_handler_block proto __cdecl \
	      instance: gpointer,
	    handler_id: gulong

g_signal_handler_unblock proto __cdecl \
	      instance: gpointer,
	    handler_id: gulong

g_signal_handler_disconnect proto __cdecl \
	      instance: gpointer,
	    handler_id: gulong

;gboolean
g_signal_handler_is_connected proto __cdecl \
	      instance: gpointer,
	    handler_id: gulong

;gulong
g_signal_handler_find proto __cdecl \
	      instance: gpointer,
		  mask: GSignalMatchType,
	     signal_id: guint,
		detail: GQuark,
	       closure: ptr GClosure,
		  func: gpointer,
		  data: gpointer

;guint
g_signal_handlers_block_matched proto __cdecl \
	      instance: gpointer,
		  mask: GSignalMatchType,
	     signal_id: guint,
		detail: GQuark,
	       closure: ptr GClosure,
		  func: gpointer,
		  data: gpointer

;guint
g_signal_handlers_unblock_matched proto __cdecl \
	      instance: gpointer,
		  mask: GSignalMatchType,
	     signal_id: guint,
		detail: GQuark,
	       closure: ptr GClosure,
		  func: gpointer,
		  data: gpointer

;guint
g_signal_handlers_disconnect_matched proto __cdecl \
	      instance: gpointer,
		  mask: GSignalMatchType,
	     signal_id: guint,
		detail: GQuark,
	       closure: ptr GClosure,
		  func: gpointer,
		  data: gpointer

g_signal_override_class_closure proto __cdecl \
	     signal_id: guint,
	 instance_type: GType,
	 class_closure: ptr GClosure

g_signal_override_class_handler proto __cdecl \
	   signal_name: ptr gchar,
	 instance_type: GType,
	 class_handler: GCallback

g_signal_chain_from_overridden proto __cdecl \
   instance_and_params: ptr GValue,
	  return_value: ptr GValue

g_signal_chain_from_overridden_handler proto _CDecl \
	      instance: gpointer,
		      : vararg


g_signal_connect macro instance, detailed_signal, c_handler, data
	exitm<g_signal_connect_data(instance, detailed_signal, c_handler, data, NULL, 0)>
	endm
g_signal_connect_after macro instance, detailed_signal, c_handler, data
	exitm<g_signal_connect_data(instance, detailed_signal, c_handler, data, NULL, G_CONNECT_AFTER)>
	endm
g_signal_connect_swapped macro instance, detailed_signal, c_handler, data
	exitm<g_signal_connect_data(instance, detailed_signal, c_handler, data, NULL, G_CONNECT_SWAPPED)>
	endm
g_signal_handlers_disconnect_by_func macro instance, func, data
	exitm<g_signal_handlers_disconnect_matched(instance, G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA, 0, 0, NULL, func, data)>
	endm
g_signal_handlers_disconnect_by_data macro instance, data
	exitm<g_signal_handlers_disconnect_matched(instance, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, data)>
	endm
g_signal_handlers_block_by_func macro instance, func, data
	exitm<g_signal_handlers_block_matched(instance, G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA, 0, 0, NULL, func, data)>
	endm
g_signal_handlers_unblock_by_func macro instance, func, data
	exitm<g_signal_handlers_unblock_matched(instance, G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA, 0, 0, NULL, func, data)>
	endm

;gboolean
g_signal_accumulator_true_handled proto __cdecl \
		 ihint: ptr GSignalInvocationHint,
	   return_accu: ptr GValue,
	handler_return: ptr GValue,
		 dummy: gpointer


;gboolean
g_signal_accumulator_first_wins proto __cdecl \
		 ihint: ptr GSignalInvocationHint,
	   return_accu: ptr GValue,
	handler_return: ptr GValue,
		 dummy: gpointer

g_signal_handlers_destroy proto __cdecl \
	      instance: gpointer

_g_signals_destroy proto __cdecl \
		 itype: GType

endif

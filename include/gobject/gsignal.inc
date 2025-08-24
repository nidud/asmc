ifndef __G_SIGNAL_H__
define __G_SIGNAL_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gclosure.inc
include gobject/gvalue.inc
include gobject/gparam.inc
include gobject/gmarshal.inc

GSignalCMarshaller	 typedef GClosureMarshal
GSignalCVaMarshaller	 typedef GVaClosureMarshal

CALLBACK(GSignalEmissionHook, :ptr, :guint, :ptr, :gpointer)
CALLBACK(GSignalAccumulator, :ptr, :ptr, :ptr, :gpointer)

.enum GSignalFlags {
  G_SIGNAL_RUN_FIRST	= 1 shl 0,
  G_SIGNAL_RUN_LAST	= 1 shl 1,
  G_SIGNAL_RUN_CLEANUP	= 1 shl 2,
  G_SIGNAL_NO_RECURSE	= 1 shl 3,
  G_SIGNAL_DETAILED	= 1 shl 4,
  G_SIGNAL_ACTION	= 1 shl 5,
  G_SIGNAL_NO_HOOKS	= 1 shl 6,
  G_SIGNAL_MUST_COLLECT = 1 shl 7,
  G_SIGNAL_DEPRECATED	= 1 shl 8,
  G_SIGNAL_ACCUMULATOR_FIRST_RUN    = 1 shl 17,
}

define G_SIGNAL_FLAGS_MASK  0x1ff

.enum GConnectFlags {
  G_CONNECT_AFTER	= 1 shl 0,
  G_CONNECT_SWAPPED	= 1 shl 1
}

.enum GSignalMatchType {
  G_SIGNAL_MATCH_ID	   = 1 shl 0,
  G_SIGNAL_MATCH_DETAIL	   = 1 shl 1,
  G_SIGNAL_MATCH_CLOSURE   = 1 shl 2,
  G_SIGNAL_MATCH_FUNC	   = 1 shl 3,
  G_SIGNAL_MATCH_DATA	   = 1 shl 4,
  G_SIGNAL_MATCH_UNBLOCKED = 1 shl 5
}

define G_SIGNAL_MATCH_MASK  0x3f
define	G_SIGNAL_TYPE_STATIC_SCOPE (G_TYPE_FLAG_RESERVED_ID_BIT)

GSignalInvocationHint	struct
signal_id		guint ?
detail			GQuark ?
run_type		GSignalFlags ?
GSignalInvocationHint	ends

GSignalQuery		struct
signal_id		guint ?
signal_name		ptr gchar ?
itype			GType ?
signal_flags		GSignalFlags ?
return_type		GType ?
n_params		guint ?
param_types		ptr GType ?
GSignalQuery		ends

g_signal_newv proto :ptr, :GType, :GSignalFlags, :ptr, :GSignalAccumulator, :gpointer, :GSignalCMarshaller, :GType, :guint, :ptr
g_signal_new_valist proto :ptr, :GType, :GSignalFlags, :ptr, :GSignalAccumulator, :gpointer, :GSignalCMarshaller, :GType, :guint, :va_list
g_signal_new proto :ptr, :GType, :GSignalFlags, :guint, :GSignalAccumulator, :gpointer, :GSignalCMarshaller, :GType, :guint, :vararg
g_signal_new_class_handler proto :ptr, :GType, :GSignalFlags, :GCallback, :GSignalAccumulator, :gpointer, :GSignalCMarshaller, :GType, :guint, :vararg
g_signal_set_va_marshaller proto :guint, :GType, :GSignalCVaMarshaller

g_signal_emitv proto :ptr, :guint, :GQuark, :ptr
g_signal_emit_valist proto :gpointer, :guint, :GQuark, :va_list
g_signal_emit proto :gpointer, :guint, :GQuark, :vararg
g_signal_emit_by_name proto :gpointer, :ptr, :vararg
g_signal_lookup proto :ptr, :GType
g_signal_name proto :guint
g_signal_query proto :guint, :ptr
g_signal_list_ids proto :GType, :ptr
g_signal_is_valid_name proto :ptr
g_signal_parse_name proto :ptr, :GType, :ptr, :ptr, :gboolean
g_signal_get_invocation_hint proto :gpointer

g_signal_stop_emission proto :gpointer, :guint, :GQuark
g_signal_stop_emission_by_name proto :gpointer, :ptr
g_signal_add_emission_hook proto :guint, :GQuark, :GSignalEmissionHook, :gpointer, :GDestroyNotify
g_signal_remove_emission_hook proto :guint, :gulong

g_signal_has_handler_pending proto :gpointer, :guint, :GQuark, :gboolean
g_signal_connect_closure_by_id proto :gpointer, :guint, :GQuark, :ptr, :gboolean
g_signal_connect_closure proto :gpointer, :ptr, :ptr, :gboolean
g_signal_connect_data proto :gpointer, :ptr, :GCallback, :gpointer, :GClosureNotify, :GConnectFlags
g_signal_handler_block proto :gpointer, :gulong
g_signal_handler_unblock proto :gpointer, :gulong
g_signal_handler_disconnect proto :gpointer, :gulong
g_signal_handler_is_connected proto :gpointer, :gulong
g_signal_handler_find proto :gpointer, :GSignalMatchType, :guint, :GQuark, :ptr, :gpointer, :gpointer
g_signal_handlers_block_matched proto :gpointer, :GSignalMatchType, :guint, :GQuark, :ptr, :gpointer, :gpointer
g_signal_handlers_unblock_matched proto :gpointer, :GSignalMatchType, :guint, :GQuark, :ptr, :gpointer, :gpointer
g_signal_handlers_disconnect_matched proto :gpointer, :GSignalMatchType, :guint, :GQuark, :ptr, :gpointer, :gpointer

g_clear_signal_handler proto :ptr, :gpointer

g_clear_signal_handler macro handler_id_ptr, instance
  exitm<.err>
  endm

g_signal_override_class_closure proto :guint, :GType, :ptr
g_signal_override_class_handler proto :ptr, :GType, :GCallback
g_signal_chain_from_overridden proto :ptr, :ptr
g_signal_chain_from_overridden_handler proto :gpointer, :vararg

g_signal_connect macro instance, detailed_signal, c_handler, data
  exitm<g_signal_connect_data (instance, detailed_signal, c_handler, data, NULL, 0)>
  endm

g_signal_connect_after macro instance, detailed_signal, c_handler, data
  exitm<g_signal_connect_data (instance, detailed_signal, c_handler, data, NULL, G_CONNECT_AFTER)>
  endm

g_signal_connect_swapped macro instance, detailed_signal, c_handler, data
  exitm<g_signal_connect_data (instance, detailed_signal, c_handler, data, NULL, G_CONNECT_SWAPPED)>
  endm

g_signal_handlers_disconnect_by_func macro instance, func, data
  exitm<g_signal_handlers_disconnect_matched (instance, GSignalMatchType(G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA), 0, 0, NULL, func, data)>
  endm


g_signal_handlers_disconnect_by_data macro instance, data
  exitm<g_signal_handlers_disconnect_matched (instance, G_SIGNAL_MATCH_DATA, 0, 0, NULL, NULL, data)>
  endm


g_signal_handlers_block_by_func macro instance, func, data
  exitm<g_signal_handlers_block_matched	     (instance, GSignalMatchType (G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA), 0, 0, NULL, func, data)>
  endm

g_signal_handlers_unblock_by_func macro instance, func, data
  exitm<g_signal_handlers_unblock_matched    (instance, GSignalMatchType (G_SIGNAL_MATCH_FUNC or G_SIGNAL_MATCH_DATA), 0, 0, NULL, func, data)>
  endm


g_signal_accumulator_true_handled proto :ptr, :ptr, :ptr, :gpointer
g_signal_accumulator_first_wins proto :ptr, :ptr, :ptr, :gpointer

g_signal_handlers_destroy proto :gpointer
_g_signals_destroy proto :GType

endif

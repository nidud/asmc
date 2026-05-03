ifndef __G_SLICE_H__
define __G_SLICE_H__

if not defined (__GLIB_H_INSIDE__) and not defined (GLIB_COMPILATION)
.err <"Only glib.h can be included directly.">
endif

include glib/gtypes.inc
include string.inc

g_slice_free1 proto :gsize, :gpointer
g_slice_free_chain_with_offset proto :gsize, :gpointer, :gsize
g_slice_new macro type
  exitm<(g_slice_alloc (sizeof (type)))>
  endm


if defined (__GNUC__) and (__GNUC__ ge 2) and defined (__OPTIMIZE__)
g_slice_new0 macro type
  exitm<.err>
  endm
else
g_slice_new0 macro type
  exitm<(g_slice_alloc0 (sizeof (type)))>
  endm
endif

g_slice_dup macro type, mem
  exitm<.err>
  endm
g_slice_free macro type, mem
  exitm<.err>
  endm
g_slice_free_chain macro type, mem_chain, next
  exitm<.err>
  endm

.enum GSliceConfig {
  G_SLICE_CONFIG_ALWAYS_MALLOC = 1,
  G_SLICE_CONFIG_BYPASS_MAGAZINES,
  G_SLICE_CONFIG_WORKING_SET_MSECS,
  G_SLICE_CONFIG_COLOR_INCREMENT,
  G_SLICE_CONFIG_CHUNK_SIZES,
  G_SLICE_CONFIG_CONTENTION_COUNTER
}

g_slice_set_config proto :GSliceConfig, :gint64
g_slice_get_config proto :GSliceConfig
g_slice_get_config_state proto :GSliceConfig, :gint64, :ptr

ifdef G_ENABLE_DEBUG
g_slice_debug_tree_statistics proto
endif

endif

ifndef __G_TYPE_PLUGIN_H__
define __G_TYPE_PLUGIN_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

define G_TYPE_TYPE_PLUGIN		<g_type_plugin_get_type ()>
G_TYPE_PLUGIN macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TYPE_PLUGIN, GTypePlugin))>
  endm
G_TYPE_PLUGIN_CLASS macro vtable
  exitm<(G_TYPE_CHECK_CLASS_CAST ((vtable), G_TYPE_TYPE_PLUGIN, GTypePluginClass))>
  endm
G_IS_TYPE_PLUGIN macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TYPE_PLUGIN))>
  endm
G_IS_TYPE_PLUGIN_CLASS macro vtable
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((vtable), G_TYPE_TYPE_PLUGIN))>
  endm
G_TYPE_PLUGIN_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_TYPE_PLUGIN, GTypePluginClass))>
  endm


CALLBACK(GTypePluginUse, :ptr)
CALLBACK(GTypePluginUnuse, :ptr)
CALLBACK(GTypePluginCompleteTypeInfo, :ptr, :GType, :ptr, :ptr)
CALLBACK(GTypePluginCompleteInterfaceInfo, :ptr, :GType, :GType, :ptr)

_GTypePluginClass	struct
base_iface		GTypeInterface <>
use_plugin		GTypePluginUse ?
unuse_plugin		GTypePluginUnuse ?
complete_type_info	GTypePluginCompleteTypeInfo ?
complete_interface_info GTypePluginCompleteInterfaceInfo ?
_GTypePluginClass	ends
GTypePluginClass	typedef _GTypePluginClass


g_type_plugin_get_type proto
g_type_plugin_use proto :ptr
g_type_plugin_unuse proto :ptr
g_type_plugin_complete_type_info proto :ptr, :GType, :ptr, :ptr
g_type_plugin_complete_interface_info proto :ptr, :GType, :GType, :ptr

endif

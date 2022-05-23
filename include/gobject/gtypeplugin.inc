ifndef __G_TYPE_PLUGIN_H__
define __G_TYPE_PLUGIN_H__
if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc

G_TYPE_TYPE_PLUGIN equ <g_type_plugin_get_type>
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

CALLBACKC(GTypePluginUse, :ptr GTypePlugin)
CALLBACKC(GTypePluginUnuse, :ptr GTypePlugin)
CALLBACKC(GTypePluginCompleteTypeInfo, :ptr GTypePlugin, :GType, :ptr GTypeInfo, :ptr GTypeValueTable)
CALLBACKC(GTypePluginCompleteInterfaceInfo, :ptr GTypePlugin, :GType, :GType, :ptr GInterfaceInfo)

GTypePluginClass	STRUC
base_iface		GTypeInterface <>
use_plugin		GTypePluginUse ?
unuse_plugin		GTypePluginUnuse ?
complete_type_info	GTypePluginCompleteTypeInfo ?
complete_interface_info GTypePluginCompleteInterfaceInfo ?
GTypePluginClass	ENDS


;GType
g_type_plugin_get_type proto __cdecl
;void
g_type_plugin_use proto __cdecl \
		plugin: ptr GTypePlugin

;void
g_type_plugin_unuse proto __cdecl \
		plugin: ptr GTypePlugin

;void
g_type_plugin_complete_type_info proto __cdecl \
		plugin: ptr GTypePlugin,
		g_type: GType,
		  info: ptr GTypeInfo,
	   value_table: ptr GTypeValueTable

;void
g_type_plugin_complete_interface_info proto __cdecl \
		plugin: ptr GTypePlugin,
	 instance_type: GType,
	interface_type: GType,
		  info: ptr GInterfaceInfo

endif

ifndef __G_DBUS_INTROSPECTION_H__
define __G_DBUS_INTROSPECTION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

_GDBusAnnotationInfo    struct
ref_count               gint ?
key                     ptr gchar ?
value                   ptr gchar ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusAnnotationInfo    ends
GDBusAnnotationInfo     typedef _GDBusAnnotationInfo

_GDBusArgInfo           struct
ref_count               gint ?
name                    ptr gchar ?
signature               ptr gchar ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusArgInfo           ends
GDBusArgInfo            typedef _GDBusArgInfo

_GDBusMethodInfo        struct
ref_count               gint ?
name                    ptr gchar ?
in_args                 ptr GDBusArgInfo ?
out_args                ptr GDBusArgInfo ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusMethodInfo        ends
GDBusMethodInfo         typedef _GDBusMethodInfo

_GDBusSignalInfo        struct
ref_count               gint ?
name                    ptr gchar ?
args                    ptr GDBusArgInfo ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusSignalInfo        ends
GDBusSignalInfo         typedef _GDBusSignalInfo

_GDBusPropertyInfo      struct
ref_count               gint ?
name                    ptr gchar ?
signature               ptr gchar ?
flags                   GDBusPropertyInfoFlags ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusPropertyInfo      ends
GDBusPropertyInfo       typedef _GDBusPropertyInfo

_GDBusInterfaceInfo     struct
ref_count               gint ?
name                    ptr gchar ?
methods                 ptr GDBusMethodInfo ?
signals                 ptr GDBusSignalInfo ?
properties              ptr GDBusPropertyInfo ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusInterfaceInfo     ends
GDBusInterfaceInfo      typedef _GDBusInterfaceInfo

_GDBusNodeInfo          struct
ref_count               gint ?
path                    ptr gchar ?
interfaces              ptr GDBusInterfaceInfo ?
nodes                   ptr GDBusNodeInfo ?
annotations             ptr GDBusAnnotationInfo ?
_GDBusNodeInfo          ends
GDBusNodeInfo           typedef _GDBusNodeInfo

g_dbus_annotation_info_lookup proto :ptr, :ptr
g_dbus_interface_info_lookup_method proto :ptr, :ptr
g_dbus_interface_info_lookup_signal proto :ptr, :ptr
g_dbus_interface_info_lookup_property proto :ptr, :ptr
g_dbus_interface_info_cache_build proto :ptr
g_dbus_interface_info_cache_release proto :ptr

g_dbus_interface_info_generate_xml proto :ptr, :guint, :ptr

g_dbus_node_info_new_for_xml proto :ptr, :ptr
g_dbus_node_info_lookup_interface proto :ptr, :ptr
g_dbus_node_info_generate_xml proto :ptr, :guint, :ptr

g_dbus_node_info_ref proto :ptr
g_dbus_interface_info_ref proto :ptr
g_dbus_method_info_ref proto :ptr
g_dbus_signal_info_ref proto :ptr
g_dbus_property_info_ref proto :ptr
g_dbus_arg_info_ref proto :ptr
g_dbus_annotation_info_ref proto :ptr

g_dbus_node_info_unref proto :ptr
g_dbus_interface_info_unref proto :ptr
g_dbus_method_info_unref proto :ptr
g_dbus_signal_info_unref proto :ptr
g_dbus_property_info_unref proto :ptr
g_dbus_arg_info_unref proto :ptr
g_dbus_annotation_info_unref proto :ptr

define G_TYPE_DBUS_NODE_INFO       <g_dbus_node_info_get_type ()>
define G_TYPE_DBUS_INTERFACE_INFO  <g_dbus_interface_info_get_type ()>
define G_TYPE_DBUS_METHOD_INFO     <g_dbus_method_info_get_type ()>
define G_TYPE_DBUS_SIGNAL_INFO     <g_dbus_signal_info_get_type ()>
define G_TYPE_DBUS_PROPERTY_INFO   <g_dbus_property_info_get_type ()>
define G_TYPE_DBUS_ARG_INFO        <g_dbus_arg_info_get_type ()>
define G_TYPE_DBUS_ANNOTATION_INFO <g_dbus_annotation_info_get_type ()>

g_dbus_node_info_get_type proto
g_dbus_interface_info_get_type proto
g_dbus_method_info_get_type proto
g_dbus_signal_info_get_type proto
g_dbus_property_info_get_type proto
g_dbus_arg_info_get_type proto
g_dbus_annotation_info_get_type proto

endif

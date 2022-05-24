ifndef __G_RESOURCE_H__
define __G_RESOURCE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_RESOURCE <g_resource_get_type ()>

define G_RESOURCE_ERROR <g_resource_error_quark ()>
g_resource_error_quark proto

_GStaticResource        struct
data                    ptr guint8 ?
data_len                gsize ?
resource                ptr GResource ?
next                    ptr GStaticResource ?
padding                 gpointer ?
_GStaticResource        ends
GStaticResource         typedef _GStaticResource

g_resource_get_type proto
g_resource_new_from_data proto :ptr, :ptr
g_resource_ref proto :ptr
g_resource_unref proto :ptr
g_resource_load proto :ptr, :ptr
g_resource_open_stream proto :ptr, :ptr, :GResourceLookupFlags, :ptr
g_resource_lookup_data proto :ptr, :ptr, :GResourceLookupFlags, :ptr
g_resource_enumerate_children proto :ptr, :ptr, :GResourceLookupFlags, :ptr
g_resource_get_info proto :ptr, :ptr, :GResourceLookupFlags, :ptr, :ptr, :ptr

g_resources_register proto :ptr
g_resources_unregister proto :ptr
g_resources_open_stream proto :ptr, :GResourceLookupFlags, :ptr
g_resources_lookup_data proto :ptr, :GResourceLookupFlags, :ptr
g_resources_enumerate_children proto :ptr, :GResourceLookupFlags, :ptr
g_resources_get_info proto :ptr, :GResourceLookupFlags, :ptr, :ptr, :ptr

g_static_resource_init proto :ptr
g_static_resource_fini proto :ptr
g_static_resource_get_resource proto :ptr

endif

ifndef __G_VFS_H__
define __G_VFS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_VFS         <g_vfs_get_type>
G_VFS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_VFS, GVfs))>
  endm
G_VFS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_VFS, GVfsClass))>
  endm
G_VFS_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_VFS, GVfsClass))>
  endm
G_IS_VFS macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_VFS))>
  endm
G_IS_VFS_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_VFS))>
  endm


CALLBACK(GVfsFileLookupFunc, :ptr, :ptr, :gpointer)

define G_VFS_EXTENSION_POINT_NAME <"gio-vfs">


_GVfs                   struct
parent_instance         GObject <>
_GVfs                   ends

_GVfsClass              struct
parent_class            GObjectClass <>
is_active               proc :ptr
get_file_for_path       proc :ptr, :ptr
get_file_for_uri        proc :ptr, :ptr
get_supported_uri_schemes proc :ptr
parse_name              proc :ptr, :ptr
local_file_add_info     proc :ptr, :ptr, :guint64, :ptr, :ptr, :ptr, :ptr, :ptr
add_writable_namespaces proc :ptr, :ptr
local_file_set_attributes proc :ptr, :ptr, :ptr, :GFileQueryInfoFlags, :ptr, :ptr
local_file_removed      proc :ptr, :ptr
local_file_moved        proc :ptr, :ptr, :ptr
deserialize_icon        proc :ptr, :ptr
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_GVfsClass              ends
GVfsClass               typedef _GVfsClass

g_vfs_get_type proto
g_vfs_is_active proto :ptr
g_vfs_get_file_for_path proto :ptr, :ptr
g_vfs_get_file_for_uri proto :ptr, :ptr
g_vfs_get_supported_uri_schemes proto :ptr
g_vfs_parse_name proto :ptr, :ptr
g_vfs_get_default proto
g_vfs_get_local proto
g_vfs_register_uri_scheme proto :ptr, :ptr, :GVfsFileLookupFunc, :gpointer, :GDestroyNotify, :GVfsFileLookupFunc, :gpointer, :GDestroyNotify
g_vfs_unregister_uri_scheme proto :ptr, :ptr

endif

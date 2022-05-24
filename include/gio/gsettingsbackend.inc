ifndef __G_SETTINGS_BACKEND_H__
define __G_SETTINGS_BACKEND_H__

if not defined (G_SETTINGS_ENABLE_BACKEND) and not defined (GIO_COMPILATION)
.err <"You must define G_SETTINGS_ENABLE_BACKEND before including gio/gsettingsbackend.h.">
endif

define __GIO_GIO_H_INSIDE__
include gio/giotypes.inc
undef __GIO_GIO_H_INSIDE__

define G_TYPE_SETTINGS_BACKEND                             <g_settings_backend_get_type ()>
G_SETTINGS_BACKEND macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SETTINGS_BACKEND, GSettingsBackend))>
  endm
G_SETTINGS_BACKEND_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SETTINGS_BACKEND, GSettingsBackendClass))>
  endm
G_IS_SETTINGS_BACKEND macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SETTINGS_BACKEND))>
  endm
G_IS_SETTINGS_BACKEND_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SETTINGS_BACKEND))>
  endm
G_SETTINGS_BACKEND_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SETTINGS_BACKEND, GSettingsBackendClass))>
  endm

define G_SETTINGS_BACKEND_EXTENSION_POINT_NAME <"gsettings-backend">

;GSettingsBackendPrivate typedef _GSettingsBackendPrivate

_GSettingsBackendClass  struct
parent_class            GObjectClass <>
read                    proc :ptr, :ptr, :ptr, :gboolean
get_writable            proc :ptr, :ptr
write                   proc :ptr, :ptr, :ptr, :gpointer
write_tree              proc :ptr, :ptr, :gpointer
reset                   proc :ptr, :ptr, :gpointer
subscribe               proc :ptr, :ptr
unsubscribe             proc :ptr, :ptr
sync                    proc :ptr
get_permission          proc :ptr, :ptr
read_user_value         proc :ptr, :ptr, :ptr
padding                 gpointer 23 dup(?)
_GSettingsBackendClass  ends
GSettingsBackendClass   typedef _GSettingsBackendClass

_GSettingsBackend       struct
parent_instance         GObject <>
priv                    ptr GSettingsBackendPrivate ?
_GSettingsBackend       ends
GSettingsBackend        typedef _GSettingsBackend

g_settings_backend_get_type proto

g_settings_backend_changed proto :ptr, :ptr, :gpointer
g_settings_backend_path_changed proto :ptr, :ptr, :gpointer
g_settings_backend_flatten_tree proto :ptr, :ptr, :ptr, :ptr
g_settings_backend_keys_changed proto :ptr, :ptr, :ptr, :gpointer

g_settings_backend_path_writable_changed proto :ptr, :ptr
g_settings_backend_writable_changed proto :ptr, :ptr
g_settings_backend_changed_tree proto :ptr, :ptr, :gpointer

g_settings_backend_get_default proto
g_keyfile_settings_backend_new proto :ptr, :ptr, :ptr
g_null_settings_backend_new proto
g_memory_settings_backend_new proto

endif

ifndef __G_SETTINGS_H__
define __G_SETTINGS_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gsettingsschema.inc
include gio/giotypes.inc

define G_TYPE_SETTINGS                                     <g_settings_get_type ()>
G_SETTINGS macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_SETTINGS, GSettings))>
  endm
G_SETTINGS_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_SETTINGS, GSettingsClass))>
  endm
G_IS_SETTINGS macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_SETTINGS))>
  endm
G_IS_SETTINGS_CLASS macro class
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_SETTINGS))>
  endm
G_SETTINGS_GET_CLASS macro inst
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), G_TYPE_SETTINGS, GSettingsClass))>
  endm

;GSettingsPrivate        typedef _GSettingsPrivate

_GSettingsClass         struct
parent_class            GObjectClass <>
writable_changed        proc :ptr, :ptr
changed                 proc :ptr, :ptr
writable_change_event   proc :ptr, :GQuark
change_event            proc :ptr, :ptr, :gint
padding                 gpointer 20 dup(?)
_GSettingsClass         ends
GSettingsClass          typedef _GSettingsClass

_GSettings              struct
parent_instance         GObject <>
priv                    ptr GSettingsPrivate ?
_GSettings              ends
GSettings               typedef _GSettings

g_settings_get_type proto
g_settings_list_schemas proto
g_settings_list_relocatable_schemas proto
g_settings_new proto :ptr
g_settings_new_with_path proto :ptr, :ptr
g_settings_new_with_backend proto :ptr, :ptr
g_settings_new_with_backend_and_path proto :ptr, :ptr, :ptr
g_settings_new_full proto :ptr, :ptr, :ptr
g_settings_list_children proto :ptr
g_settings_list_keys proto :ptr
g_settings_get_range proto :ptr, :ptr
g_settings_range_check proto :ptr, :ptr, :ptr

g_settings_set_value proto :ptr, :ptr, :ptr
g_settings_get_value proto :ptr, :ptr

g_settings_get_user_value proto :ptr, :ptr
g_settings_get_default_value proto :ptr, :ptr

g_settings_set proto :ptr, :ptr, :ptr, :vararg
g_settings_get proto :ptr, :ptr, :ptr, :vararg
g_settings_reset proto :ptr, :ptr

g_settings_get_int proto :ptr, :ptr
g_settings_set_int proto :ptr, :ptr, :gint
g_settings_get_int64 proto :ptr, :ptr
g_settings_set_int64 proto :ptr, :ptr, :gint64
g_settings_get_uint proto :ptr, :ptr
g_settings_set_uint proto :ptr, :ptr, :guint
g_settings_get_uint64 proto :ptr, :ptr
g_settings_set_uint64 proto :ptr, :ptr, :guint64
g_settings_get_string proto :ptr, :ptr
g_settings_set_string proto :ptr, :ptr, :ptr
g_settings_get_boolean proto :ptr, :ptr
g_settings_set_boolean proto :ptr, :ptr, :gboolean
g_settings_get_double proto :ptr, :ptr
g_settings_set_double proto :ptr, :ptr, :gdouble
g_settings_get_strv proto :ptr, :ptr
g_settings_set_strv proto :ptr, :ptr, :ptr
g_settings_get_enum proto :ptr, :ptr
g_settings_set_enum proto :ptr, :ptr, :gint
g_settings_get_flags proto :ptr, :ptr
g_settings_set_flags proto :ptr, :ptr, :guint
g_settings_get_child proto :ptr, :ptr

g_settings_is_writable proto :ptr, :ptr

g_settings_delay proto :ptr
g_settings_apply proto :ptr
g_settings_revert proto :ptr
g_settings_get_has_unapplied proto :ptr
g_settings_sync proto

CALLBACK(GSettingsBindSetMapping, :ptr, :ptr, :gpointer)
CALLBACK(GSettingsBindGetMapping, :ptr, :ptr, :gpointer)
CALLBACK(GSettingsGetMapping, :ptr, :ptr, :gpointer)

.enum GSettingsBindFlags {
  G_SETTINGS_BIND_DEFAULT,
  G_SETTINGS_BIND_GET            = (1 shl 0),
  G_SETTINGS_BIND_SET            = (1 shl 1),
  G_SETTINGS_BIND_NO_SENSITIVITY = (1 shl 2),
  G_SETTINGS_BIND_GET_NO_CHANGES = (1 shl 3),
  G_SETTINGS_BIND_INVERT_BOOLEAN = (1 shl 4)
}

g_settings_bind proto :ptr, :ptr, :gpointer, :ptr, :GSettingsBindFlags
g_settings_bind_with_mapping proto :ptr, :ptr, :gpointer, :ptr, :GSettingsBindFlags, :GSettingsBindGetMapping, :GSettingsBindSetMapping, :gpointer, :GDestroyNotify
g_settings_bind_writable proto :ptr, :ptr, :gpointer, :ptr, :gboolean
g_settings_unbind proto :gpointer, :ptr
g_settings_create_action proto :ptr, :ptr
g_settings_get_mapped proto :ptr, :ptr, :GSettingsGetMapping, :gpointer

endif

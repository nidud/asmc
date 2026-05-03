ifndef __G_DRIVE_H__
define __G_DRIVE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_DRIVE_IDENTIFIER_KIND_UNIX_DEVICE <"unix-device">

define G_TYPE_DRIVE           <g_drive_get_type ()>
G_DRIVE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_DRIVE, GDrive))>
  endm
G_IS_DRIVE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_DRIVE))>
  endm
G_DRIVE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_DRIVE, GDriveIface))>
  endm


GDriveIface             struct
g_iface                 GTypeInterface <>
changed                 proc :ptr
disconnected            proc :ptr
eject_button            proc :ptr
get_name                proc :ptr
get_icon                proc :ptr
has_volumes             proc :ptr
get_volumes             proc :ptr
is_media_removable      proc :ptr
has_media               proc :ptr
is_media_check_automatic proc :ptr
can_eject               proc :ptr
can_poll_for_media      proc :ptr
eject                   proc :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer
eject_finish            proc :ptr, :ptr, :ptr
poll_for_media          proc :ptr, :ptr, :GAsyncReadyCallback, :gpointer
poll_for_media_finish   proc :ptr, :ptr, :ptr
get_identifier          proc :ptr, :ptr
enumerate_identifiers   proc :ptr
get_start_stop_type     proc :ptr
can_start               proc :ptr
can_start_degraded      proc :ptr
start                   proc :ptr, :GDriveStartFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
start_finish            proc :ptr, :ptr, :ptr
can_stop                proc :ptr
stop                    proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
stop_finish             proc :ptr, :ptr, :ptr
stop_button             proc :ptr
eject_with_operation    proc :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
eject_with_operation_finish proc :ptr, :ptr, :ptr
get_sort_key            proc :ptr
get_symbolic_icon       proc :ptr
is_removable            proc :ptr
GDriveIface             ends

g_drive_get_type proto

g_drive_get_name proto :ptr
g_drive_get_icon proto :ptr
g_drive_get_symbolic_icon proto :ptr
g_drive_has_volumes proto :ptr
g_drive_get_volumes proto :ptr
g_drive_is_removable proto :ptr
g_drive_is_media_removable proto :ptr
g_drive_has_media proto :ptr
g_drive_is_media_check_automatic proto :ptr
g_drive_can_poll_for_media proto :ptr
g_drive_can_eject proto :ptr
g_drive_eject proto :ptr, :GMountUnmountFlags, :ptr, :GAsyncReadyCallback, :gpointer

g_drive_eject_finish proto :ptr, :ptr, :ptr
g_drive_poll_for_media proto :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_drive_poll_for_media_finish proto :ptr, :ptr, :ptr
g_drive_get_identifier proto :ptr, :ptr
g_drive_enumerate_identifiers proto :ptr

g_drive_get_start_stop_type proto :ptr

g_drive_can_start proto :ptr
g_drive_can_start_degraded proto :ptr
g_drive_start proto :ptr, :GDriveStartFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_drive_start_finish proto :ptr, :ptr, :ptr

g_drive_can_stop proto :ptr
g_drive_stop proto :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_drive_stop_finish proto :ptr, :ptr, :ptr

g_drive_eject_with_operation proto :ptr, :GMountUnmountFlags, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_drive_eject_with_operation_finish proto :ptr, :ptr, :ptr

g_drive_get_sort_key proto :ptr

endif

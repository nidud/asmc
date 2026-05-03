ifndef __G_MOUNT_OPERATION_H__
define __G_MOUNT_OPERATION_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_MOUNT_OPERATION         <g_mount_operation_get_type ()>
G_MOUNT_OPERATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_MOUNT_OPERATION, GMountOperation))>
  endm
G_MOUNT_OPERATION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_MOUNT_OPERATION, GMountOperationClass))>
  endm
G_IS_MOUNT_OPERATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_MOUNT_OPERATION))>
  endm
G_IS_MOUNT_OPERATION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_MOUNT_OPERATION))>
  endm
G_MOUNT_OPERATION_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_MOUNT_OPERATION, GMountOperationClass))>
  endm

GMountOperation         struct
parent_instance         GObject <>
priv                    ptr GMountOperationPrivate ?
GMountOperation         ends

GMountOperationClass    struct
parent_class            GObjectClass <>
ask_password            proc :ptr, :ptr, :ptr, :ptr, :GAskPasswordFlags
ask_question            proc :ptr, :ptr, :ptr
reply                   proc :ptr, :GMountOperationResult
aborted                 proc :ptr
show_processes          proc :ptr, :ptr, :ptr, :ptr
show_unmount_progress   proc :ptr, :ptr, :gint64, :gint64
_g_reserved1            proc
_g_reserved2            proc
_g_reserved3            proc
_g_reserved4            proc
_g_reserved5            proc
_g_reserved6            proc
_g_reserved7            proc
_g_reserved8            proc
_g_reserved9            proc
GMountOperationClass    ends

g_mount_operation_get_type proto
g_mount_operation_new proto

g_mount_operation_get_username proto :ptr
g_mount_operation_set_username proto :ptr, :ptr
g_mount_operation_get_password proto :ptr
g_mount_operation_set_password proto :ptr, :ptr
g_mount_operation_get_anonymous proto :ptr
g_mount_operation_set_anonymous proto :ptr, :gboolean
g_mount_operation_get_domain proto :ptr
g_mount_operation_set_domain proto :ptr, :ptr
g_mount_operation_get_password_save proto :ptr
g_mount_operation_set_password_save proto :ptr, :GPasswordSave
g_mount_operation_get_choice proto :ptr
g_mount_operation_set_choice proto :ptr, :sdword
g_mount_operation_reply proto :ptr, :GMountOperationResult
g_mount_operation_get_is_tcrypt_hidden_volume proto :ptr
g_mount_operation_set_is_tcrypt_hidden_volume proto :ptr, :gboolean
g_mount_operation_get_is_tcrypt_system_volume proto :ptr
g_mount_operation_set_is_tcrypt_system_volume proto :ptr, :gboolean
g_mount_operation_get_pim proto :ptr
g_mount_operation_set_pim proto :ptr, :guint

endif

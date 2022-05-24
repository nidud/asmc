ifndef __GTK_MOUNT_OPERATION_H__
define __GTK_MOUNT_OPERATION_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

define GTK_TYPE_MOUNT_OPERATION <gtk_mount_operation_get_type ()>
GTK_MOUNT_OPERATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_MOUNT_OPERATION, GtkMountOperation))>
  endm
GTK_MOUNT_OPERATION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), GTK_TYPE_MOUNT_OPERATION, GtkMountOperationClass))>
  endm
GTK_IS_MOUNT_OPERATION macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_MOUNT_OPERATION))>
  endm
GTK_IS_MOUNT_OPERATION_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_MOUNT_OPERATION))>
  endm
GTK_MOUNT_OPERATION_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_MOUNT_OPERATION, GtkMountOperationClass))>
  endm

;GtkMountOperationPrivate typedef _GtkMountOperationPrivate
if 0
_GtkMountOperation      struct
parent_instance         GMountOperation <>
priv                    ptr GtkMountOperationPrivate ?
_GtkMountOperation      ends
GtkMountOperation       typedef _GtkMountOperation

_GtkMountOperationClass struct
parent_class            GMountOperationClass <>
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkMountOperationClass ends
GtkMountOperationClass  typedef _GtkMountOperationClass
endif

gtk_mount_operation_get_type proto
gtk_mount_operation_new proto :ptr
gtk_mount_operation_is_showing proto :ptr
gtk_mount_operation_set_parent proto :ptr, :ptr
gtk_mount_operation_get_parent proto :ptr
gtk_mount_operation_set_display proto :ptr, :ptr
gtk_mount_operation_get_display proto :ptr

endif

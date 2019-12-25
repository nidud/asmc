ifndef __GTK_MOUNT_OPERATION_H__
__GTK_MOUNT_OPERATION_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

G_BEGIN_DECLS

GTK_TYPE_MOUNT_OPERATION equ <gtk_mount_operation_get_type>
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

GtkMountOperation	STRUC
;parent_instance		GMountOperation <>
priv			ptr_t ?
GtkMountOperation	ENDS

GtkMountOperationClass	STRUC
;parent_class		GMountOperationClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkMountOperationClass	ENDS


;GType
gtk_mount_operation_get_type proto __cdecl
;GMountOperation
gtk_mount_operation_new proto __cdecl \
		parent: ptr GtkWindow

;gboolean
gtk_mount_operation_is_showing proto __cdecl \
		    op: ptr GtkMountOperation

;void
gtk_mount_operation_set_parent proto __cdecl \
		    op: ptr GtkMountOperation,
		parent: ptr GtkWindow

;GtkWindow
gtk_mount_operation_get_parent proto __cdecl \
		    op: ptr GtkMountOperation

;void
gtk_mount_operation_set_screen proto __cdecl \
		    op: ptr GtkMountOperation,
		screen: ptr GdkScreen

;GdkScreen
gtk_mount_operation_get_screen proto __cdecl \
		    op: ptr GtkMountOperation


G_END_DECLS

endif

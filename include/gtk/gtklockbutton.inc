ifndef __GTK_LOCK_BUTTON_H__
__GTK_LOCK_BUTTON_H__ equ <>

include gtk/gtkbutton.inc
include gio/gio.inc

G_BEGIN_DECLS

GTK_TYPE_LOCK_BUTTON equ <gtk_lock_button_get_type>
GTK_LOCK_BUTTON macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_LOCK_BUTTON, GtkLockButton))>
	endm
GTK_LOCK_BUTTON_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_CAST ((k), GTK_LOCK_BUTTON,  GtkLockButtonClass))>
	endm
GTK_IS_LOCK_BUTTON macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_LOCK_BUTTON))>
	endm
GTK_IS_LOCK_BUTTON_CLASS macro k
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), GTK_TYPE_LOCK_BUTTON))>
	endm
GTK_LOCK_BUTTON_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), GTK_TYPE_LOCK_BUTTON, GtkLockButtonClass))>
	endm

GtkLockButton		STRUC
parent			GtkButton <>
priv			ptr_t ?
GtkLockButton		ENDS

GtkLockButtonClass	STRUC
parent_class		GtkButtonClass <>
reserved0		proc
reserved1		proc
reserved2		proc
reserved3		proc
reserved4		proc
reserved5		proc
reserved6		proc
reserved7		proc
GtkLockButtonClass	ENDS

;GType
gtk_lock_button_get_type proto __cdecl
;GtkWidget
gtk_lock_button_new proto __cdecl \
	    permission: ptr GPermission

;GPermission
gtk_lock_button_get_permission proto __cdecl \
		button: ptr GtkLockButton

;void
gtk_lock_button_set_permission proto __cdecl \
		button: ptr GtkLockButton,
	    permission: ptr GPermission

G_END_DECLS

endif

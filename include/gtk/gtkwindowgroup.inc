ifndef __GTK_WINDOW_GROUP_H__
__GTK_WINDOW_GROUP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

GTK_TYPE_WINDOW_GROUP	equ <gtk_window_group_get_type>
GTK_WINDOW_GROUP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_WINDOW_GROUP, GtkWindowGroup))>
	endm
GTK_WINDOW_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))>
	endm
GTK_IS_WINDOW_GROUP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_WINDOW_GROUP))>
	endm
GTK_IS_WINDOW_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_WINDOW_GROUP))>
	endm
GTK_WINDOW_GROUP_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_WINDOW_GROUP, GtkWindowGroupClass))>
	endm

GtkWindowGroup		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkWindowGroup		ENDS

GtkWindowGroupClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		ptr_t ?
_gtk_reserved2		ptr_t ?
_gtk_reserved3		ptr_t ?
_gtk_reserved4		ptr_t ?
GtkWindowGroupClass	ENDS


;GType
gtk_window_group_get_type proto __cdecl

;GtkWindowGroup
gtk_window_group_new proto __cdecl
;void
gtk_window_group_add_window proto __cdecl \
	  window_group: ptr GtkWindowGroup,
		window: ptr GtkWindow

;void
gtk_window_group_remove_window proto __cdecl \
	  window_group: ptr GtkWindowGroup,
		window: ptr GtkWindow

;GList
gtk_window_group_list_windows proto __cdecl \
	  window_group: ptr GtkWindowGroup


;GtkWidget
gtk_window_group_get_current_grab proto __cdecl \
	  window_group: ptr GtkWindowGroup

;GtkWidget
gtk_window_group_get_current_device_grab proto __cdecl \
	  window_group: ptr GtkWindowGroup,
		device: ptr GdkDevice

endif

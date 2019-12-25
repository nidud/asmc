ifndef __GTK_SIZE_GROUP_H__
__GTK_SIZE_GROUP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_SIZE_GROUP equ <gtk_size_group_get_type>
GTK_SIZE_GROUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SIZE_GROUP, GtkSizeGroup))>
	endm
GTK_SIZE_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SIZE_GROUP, GtkSizeGroupClass))>
	endm
GTK_IS_SIZE_GROUP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SIZE_GROUP))>
	endm
GTK_IS_SIZE_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SIZE_GROUP))>
	endm
GTK_SIZE_GROUP_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SIZE_GROUP, GtkSizeGroupClass))>
	endm

GtkSizeGroup		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkSizeGroup		ENDS

GtkSizeGroupClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSizeGroupClass	ENDS

;GType
gtk_size_group_get_type proto __cdecl

;GtkSizeGroup
gtk_size_group_new proto __cdecl \
		  mode: GtkSizeGroupMode

;void
gtk_size_group_set_mode proto __cdecl \
	    size_group: ptr GtkSizeGroup,
		  mode: GtkSizeGroupMode

;GtkSizeGroupMode
gtk_size_group_get_mode proto __cdecl \
	    size_group: ptr GtkSizeGroup

;void
gtk_size_group_set_ignore_hidden proto __cdecl \
	    size_group: ptr GtkSizeGroup,
	 ignore_hidden: gboolean

;gboolean
gtk_size_group_get_ignore_hidden proto __cdecl \
	    size_group: ptr GtkSizeGroup

;void
gtk_size_group_add_widget proto __cdecl \
	    size_group: ptr GtkSizeGroup,
		widget: ptr GtkWidget

;void
gtk_size_group_remove_widget proto __cdecl \
	    size_group: ptr GtkSizeGroup,
		widget: ptr GtkWidget

;GSList
gtk_size_group_get_widgets proto __cdecl \
	    size_group: ptr GtkSizeGroup

G_END_DECLS

endif

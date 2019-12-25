ifndef __GTK_ACTION_BAR_H__
__GTK_ACTION_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbin.inc

G_BEGIN_DECLS

GTK_TYPE_ACTION_BAR equ <gtk_action_bar_get_type>
GTK_ACTION_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ACTION_BAR, GtkActionBar))>
	endm
GTK_ACTION_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACTION_BAR, GtkActionBarClass))>
	endm
GTK_IS_ACTION_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ACTION_BAR))>
	endm
GTK_IS_ACTION_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACTION_BAR))>
	endm
GTK_ACTION_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ACTION_BAR, GtkActionBarClass))>
	endm

GtkActionBar		STRUC
bin			GtkBin <>
GtkActionBar		ENDS

GtkActionBarClass	STRUC
parent_class		GtkBinClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkActionBarClass	ENDS

;GType
gtk_action_bar_get_type proto __cdecl
;GtkWidget
gtk_action_bar_new proto __cdecl
;GtkWidget
gtk_action_bar_get_center_widget proto __cdecl \
	    action_bar: ptr GtkActionBar

;void
gtk_action_bar_set_center_widget proto __cdecl \
	    action_bar: ptr GtkActionBar,
	 center_widget: ptr GtkWidget


;void
gtk_action_bar_pack_start proto __cdecl \
	    action_bar: ptr GtkActionBar,
		 child: ptr GtkWidget

;void
gtk_action_bar_pack_end proto __cdecl \
	    action_bar: ptr GtkActionBar,
		 child: ptr GtkWidget

G_END_DECLS

endif

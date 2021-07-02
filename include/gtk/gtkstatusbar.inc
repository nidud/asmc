ifndef __GTK_STATUSBAR_H__
__GTK_STATUSBAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbox.inc

G_BEGIN_DECLS

GTK_TYPE_STATUSBAR equ <gtk_statusbar_get_type>
GTK_STATUSBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_STATUSBAR, GtkStatusbar))>
	endm
GTK_STATUSBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_STATUSBAR, GtkStatusbarClass))>
	endm
GTK_IS_STATUSBAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_STATUSBAR))>
	endm
GTK_IS_STATUSBAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_STATUSBAR))>
	endm
GTK_STATUSBAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_STATUSBAR, GtkStatusbarClass))>
	endm


GtkStatusbar		STRUC
parent_widget		GtkBox <>
priv			ptr_t ?
GtkStatusbar		ENDS

GtkStatusbarClass	STRUC
parent_class		GtkBoxClass <>
reserved		gpointer ?
text_pushed		proc :ptr GtkStatusbar, :guint, :ptr gchar
text_popped		proc :ptr GtkStatusbar, :guint, :ptr gchar
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkStatusbarClass	ENDS


;GType
gtk_statusbar_get_type proto __cdecl
;GtkWidget*
gtk_statusbar_new proto __cdecl
;guint
gtk_statusbar_get_context_id proto __cdecl \
	     statusbar: ptr GtkStatusbar,
   context_description: ptr gchar

;guint
gtk_statusbar_push proto __cdecl \
	     statusbar: ptr GtkStatusbar,
	    context_id: guint,
		  text: ptr gchar

;void
gtk_statusbar_pop proto __cdecl \
	     statusbar: ptr GtkStatusbar,
	    context_id: guint

;void
gtk_statusbar_remove proto __cdecl \
	     statusbar: ptr GtkStatusbar,
	    context_id: guint,
	    message_id: guint

;void
gtk_statusbar_remove_all proto __cdecl \
	     statusbar: ptr GtkStatusbar,
	    context_id: guint

;GtkWidget*
gtk_statusbar_get_message_area proto __cdecl \
	     statusbar: ptr GtkStatusbar

G_END_DECLS

endif

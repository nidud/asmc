ifndef __GTK_HEADER_BAR_H__
__GTK_HEADER_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcontainer.inc

G_BEGIN_DECLS

GTK_TYPE_HEADER_BAR equ <gtk_header_bar_get_type>
GTK_HEADER_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_HEADER_BAR, GtkHeaderBar))>
	endm
GTK_HEADER_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_HEADER_BAR, GtkHeaderBarClass))>
	endm
GTK_IS_HEADER_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_HEADER_BAR))>
	endm
GTK_IS_HEADER_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_HEADER_BAR))>
	endm
GTK_HEADER_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_HEADER_BAR, GtkHeaderBarClass))>
	endm

GtkHeaderBar		STRUC
container		GtkContainer <>
GtkHeaderBar		ENDS

GtkHeaderBarClass	STRUC
parent_class		GtkContainerClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkHeaderBarClass	ENDS

;GType
gtk_header_bar_get_type proto __cdecl
;GtkWidget
gtk_header_bar_new proto __cdecl
;void
gtk_header_bar_set_title proto __cdecl \
		   bar: ptr GtkHeaderBar,
		 title: ptr gchar

;const
gtk_header_bar_get_title proto __cdecl \
		   bar: ptr GtkHeaderBar

;void
gtk_header_bar_set_subtitle proto __cdecl \
		   bar: ptr GtkHeaderBar,
	      subtitle: ptr gchar

;const
gtk_header_bar_get_subtitle proto __cdecl \
		   bar: ptr GtkHeaderBar



;void
gtk_header_bar_set_custom_title proto __cdecl \
		   bar: ptr GtkHeaderBar,
	  title_widget: ptr GtkWidget

;GtkWidget
gtk_header_bar_get_custom_title proto __cdecl \
		   bar: ptr GtkHeaderBar

;void
gtk_header_bar_pack_start proto __cdecl \
		   bar: ptr GtkHeaderBar,
		 child: ptr GtkWidget

;void
gtk_header_bar_pack_end proto __cdecl \
		   bar: ptr GtkHeaderBar,
		 child: ptr GtkWidget


;gboolean
gtk_header_bar_get_show_close_button proto __cdecl \
		   bar: ptr GtkHeaderBar


;void
gtk_header_bar_set_show_close_button proto __cdecl \
		   bar: ptr GtkHeaderBar,
	       setting: gboolean


;void
gtk_header_bar_set_has_subtitle proto __cdecl \
		   bar: ptr GtkHeaderBar,
	       setting: gboolean

;gboolean
gtk_header_bar_get_has_subtitle proto __cdecl \
		   bar: ptr GtkHeaderBar


;void
gtk_header_bar_set_decoration_layout proto __cdecl \
		   bar: ptr GtkHeaderBar,
		layout: ptr gchar

;const
gtk_header_bar_get_decoration_layout proto __cdecl \
		   bar: ptr GtkHeaderBar

G_END_DECLS

endif

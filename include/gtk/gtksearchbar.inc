ifndef __GTK_SEARCH_BAR_H__
__GTK_SEARCH_BAR_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkrevealer.inc

G_BEGIN_DECLS

GTK_TYPE_SEARCH_BAR equ <gtk_search_bar_get_type>
GTK_SEARCH_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEARCH_BAR, GtkSearchBar))>
	endm
GTK_SEARCH_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SEARCH_BAR, GtkSearchBarClass))>
	endm
GTK_IS_SEARCH_BAR macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEARCH_BAR))>
	endm
GTK_IS_SEARCH_BAR_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SEARCH_BAR))>
	endm
GTK_SEARCH_BAR_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SEARCH_BAR, GtkSearchBarClass))>
	endm

GtkSearchBar		STRUC
parent			GtkBin <>
GtkSearchBar		ENDS

GtkSearchBarClass	STRUC
parent_class		GtkBinClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSearchBarClass	ENDS

;GType
gtk_search_bar_get_type proto __cdecl

;GtkWidget*
gtk_search_bar_new proto __cdecl

;void
gtk_search_bar_connect_entry proto __cdecl \
		   bar: ptr GtkSearchBar,
		 entry: ptr GtkEntry

;gboolean
gtk_search_bar_get_search_mode proto __cdecl \
		   bar: ptr GtkSearchBar

;void
gtk_search_bar_set_search_mode proto __cdecl \
		   bar: ptr GtkSearchBar,
	   search_mode: gboolean

;gboolean
gtk_search_bar_get_show_close_button proto __cdecl \
		   bar: ptr GtkSearchBar

;void
gtk_search_bar_set_show_close_button proto __cdecl \
		   bar: ptr GtkSearchBar,
	       visible: gboolean

;gboolean
gtk_search_bar_handle_event proto __cdecl \
		   bar: ptr GtkSearchBar,
		 event: ptr GdkEvent

G_END_DECLS

endif

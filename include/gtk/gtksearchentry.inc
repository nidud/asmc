ifndef __GTK_SEARCH_ENTRY_H__
__GTK_SEARCH_ENTRY_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkentry.inc

G_BEGIN_DECLS

GTK_TYPE_SEARCH_ENTRY equ <gtk_search_entry_get_type>
GTK_SEARCH_ENTRY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEARCH_ENTRY, GtkSearchEntry))>
	endm
GTK_SEARCH_ENTRY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SEARCH_ENTRY, GtkSearchEntryClass))>
	endm
GTK_IS_SEARCH_ENTRY macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEARCH_ENTRY))>
	endm
GTK_IS_SEARCH_ENTRY_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SEARCH_ENTRY))>
	endm
GTK_SEARCH_ENTRY_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SEARCH_ENTRY, GtkSearchEntryClass))>
	endm

GtkSearchEntry		STRUC
parent			GtkEntry <>
GtkSearchEntry		ENDS

GtkSearchEntryClass	STRUC
parent_class		GtkEntryClass <>
search_changed		proc :ptr GtkSearchEntry
next_match		proc :ptr GtkSearchEntry
previous_match		proc :ptr GtkSearchEntry
stop_search		proc :ptr GtkSearchEntry
GtkSearchEntryClass	ENDS

;GType
gtk_search_entry_get_type proto __cdecl

;GtkWidget*
gtk_search_entry_new proto __cdecl

;gboolean
gtk_search_entry_handle_event proto __cdecl \
		 entry: ptr GtkSearchEntry,
		 event: ptr GdkEvent

G_END_DECLS

endif

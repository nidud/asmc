ifndef __GTK_SEARCH_ENTRY_H__
define __GTK_SEARCH_ENTRY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkentry.inc

define GTK_TYPE_SEARCH_ENTRY <gtk_search_entry_get_type>
GTK_SEARCH_ENTRY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEARCH_ENTRY, GtkSearchEntry))>
  endm
GTK_IS_SEARCH_ENTRY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEARCH_ENTRY))>
  endm

;GtkSearchEntry          typedef _GtkSearchEntry

gtk_search_entry_get_type proto
gtk_search_entry_new proto
gtk_search_entry_set_key_capture_widget proto :ptr, :ptr
gtk_search_entry_get_key_capture_widget proto :ptr

endif

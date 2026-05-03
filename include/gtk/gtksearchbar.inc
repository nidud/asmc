ifndef __GTK_SEARCH_BAR_H__
define __GTK_SEARCH_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkeditable.inc

define GTK_TYPE_SEARCH_BAR <gtk_search_bar_get_type ()>
GTK_SEARCH_BAR macro obj
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SEARCH_BAR, GtkSearchBar)>
  endm
GTK_IS_SEARCH_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SEARCH_BAR))>
  endm

gtk_search_bar_get_type proto
gtk_search_bar_new proto
gtk_search_bar_connect_entry proto :ptr, :ptr
gtk_search_bar_get_search_mode proto :ptr
gtk_search_bar_set_search_mode proto :ptr, :gboolean
gtk_search_bar_get_show_close_button proto :ptr
gtk_search_bar_set_show_close_button proto :ptr, :gboolean
gtk_search_bar_set_key_capture_widget proto :ptr, :ptr
gtk_search_bar_get_key_capture_widget proto :ptr
gtk_search_bar_set_child proto :ptr, :ptr
gtk_search_bar_get_child proto :ptr

endif

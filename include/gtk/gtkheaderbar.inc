ifndef __GTK_HEADER_BAR_H__
define __GTK_HEADER_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_HEADER_BAR <gtk_header_bar_get_type>
GTK_HEADER_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_HEADER_BAR, GtkHeaderBar))>
  endm
GTK_IS_HEADER_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_HEADER_BAR))>
  endm

;GtkHeaderBar            typedef _GtkHeaderBar

gtk_header_bar_get_type proto
gtk_header_bar_new proto

gtk_header_bar_set_title_widget proto :ptr, :ptr
gtk_header_bar_get_title_widget proto :ptr
gtk_header_bar_pack_start proto :ptr, :ptr
gtk_header_bar_pack_end proto :ptr, :ptr
gtk_header_bar_remove proto :ptr, :ptr

gtk_header_bar_get_show_title_buttons proto :ptr

gtk_header_bar_set_show_title_buttons proto :ptr, :gboolean

gtk_header_bar_set_decoration_layout proto :ptr, :ptr
gtk_header_bar_get_decoration_layout proto :ptr

endif

ifndef __GTK_PANED_H__
define __GTK_PANED_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_PANED <gtk_paned_get_type ()>
GTK_PANED macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_PANED, GtkPaned))>
  endm
GTK_IS_PANED macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_PANED))>
  endm

gtk_paned_get_type proto
gtk_paned_new proto :GtkOrientation
gtk_paned_set_start_child proto :ptr, :ptr
gtk_paned_get_start_child proto :ptr
gtk_paned_set_resize_start_child proto :ptr, :gboolean
gtk_paned_get_resize_start_child proto :ptr

gtk_paned_set_end_child proto :ptr, :ptr
gtk_paned_get_end_child proto :ptr

gtk_paned_set_shrink_start_child proto :ptr, :gboolean
gtk_paned_get_shrink_start_child proto :ptr

gtk_paned_set_resize_end_child proto :ptr, :gboolean
gtk_paned_get_resize_end_child proto :ptr

gtk_paned_set_shrink_end_child proto :ptr, :gboolean
gtk_paned_get_shrink_end_child proto :ptr

gtk_paned_get_position proto :ptr
gtk_paned_set_position proto :ptr, :sdword

gtk_paned_set_wide_handle proto :ptr, :gboolean
gtk_paned_get_wide_handle proto :ptr

endif

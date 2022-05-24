ifndef __GTK_ACTION_BAR_H__
define __GTK_ACTION_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_ACTION_BAR <gtk_action_bar_get_type ()>
GTK_ACTION_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ACTION_BAR, GtkActionBar))>
  endm
GTK_IS_ACTION_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ACTION_BAR))>
  endm

;GtkActionBar		 typedef _GtkActionBar

gtk_action_bar_get_type proto
gtk_action_bar_new proto
gtk_action_bar_get_center_widget proto :ptr
gtk_action_bar_set_center_widget proto :ptr, :ptr

gtk_action_bar_pack_start proto :ptr, :ptr
gtk_action_bar_pack_end proto :ptr, :ptr

gtk_action_bar_remove proto :ptr, :ptr

gtk_action_bar_set_revealed proto :ptr, :gboolean
gtk_action_bar_get_revealed proto :ptr

endif

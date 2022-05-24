ifndef __GTK_LEVEL_BAR_H__
define __GTK_LEVEL_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_LEVEL_BAR <gtk_level_bar_get_type ()>
GTK_LEVEL_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_LEVEL_BAR, GtkLevelBar))>
  endm
GTK_IS_LEVEL_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_LEVEL_BAR))>
  endm


define GTK_LEVEL_BAR_OFFSET_LOW  <"low">
define GTK_LEVEL_BAR_OFFSET_HIGH <"high">
define GTK_LEVEL_BAR_OFFSET_FULL <"full">

;GtkLevelBar             typedef _GtkLevelBar

gtk_level_bar_get_type proto
gtk_level_bar_new proto
gtk_level_bar_new_for_interval proto :real8, :real8
gtk_level_bar_set_mode proto :ptr, :GtkLevelBarMode
gtk_level_bar_get_mode proto :ptr
gtk_level_bar_set_value proto :ptr, :real8
gtk_level_bar_get_value proto :ptr
gtk_level_bar_set_min_value proto :ptr, :real8
gtk_level_bar_get_min_value proto :ptr
gtk_level_bar_set_max_value proto :ptr, :real8
gtk_level_bar_get_max_value proto :ptr
gtk_level_bar_set_inverted proto :ptr, :gboolean
gtk_level_bar_get_inverted proto :ptr
gtk_level_bar_add_offset_value proto :ptr, :ptr, :real8
gtk_level_bar_remove_offset_value proto :ptr, :ptr
gtk_level_bar_get_offset_value proto :ptr, :ptr, :ptr

endif

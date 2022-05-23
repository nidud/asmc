ifndef __GTK_INFO_BAR_H__
define __GTK_INFO_BAR_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkenums.inc

define GTK_TYPE_INFO_BAR <gtk_info_bar_get_type>
GTK_INFO_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_INFO_BAR, GtkInfoBar))>
  endm
GTK_IS_INFO_BAR macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_INFO_BAR))>
  endm

;GtkInfoBar              typedef _GtkInfoBar

gtk_info_bar_get_type proto
gtk_info_bar_new proto
gtk_info_bar_new_with_buttons proto :ptr, :vararg
gtk_info_bar_add_action_widget proto :ptr, :ptr, :sdword
gtk_info_bar_remove_action_widget proto :ptr, :ptr
gtk_info_bar_add_button proto :ptr, :ptr, :sdword
gtk_info_bar_add_buttons proto :ptr, :ptr, :vararg
gtk_info_bar_add_child proto :ptr, :ptr
gtk_info_bar_remove_child proto :ptr, :ptr
gtk_info_bar_set_response_sensitive proto :ptr, :sdword, :gboolean
gtk_info_bar_set_default_response proto :ptr, :sdword
gtk_info_bar_response proto :ptr, :sdword
gtk_info_bar_set_message_type proto :ptr, :GtkMessageType
gtk_info_bar_get_message_type proto :ptr
gtk_info_bar_set_show_close_button proto :ptr, :gboolean
gtk_info_bar_get_show_close_button proto :ptr
gtk_info_bar_set_revealed proto :ptr, :gboolean
gtk_info_bar_get_revealed proto :ptr

endif

ifndef __GTK_EXPANDER_H__
define __GTK_EXPANDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_EXPANDER <gtk_expander_get_type ()>
GTK_EXPANDER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_EXPANDER, GtkExpander))>
  endm
GTK_IS_EXPANDER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_EXPANDER))>
  endm

gtk_expander_get_type proto
gtk_expander_new proto :ptr
gtk_expander_new_with_mnemonic proto :ptr
gtk_expander_set_expanded proto :ptr, :gboolean
gtk_expander_get_expanded proto :ptr
gtk_expander_set_label proto :ptr, :ptr
gtk_expander_get_label proto :ptr
gtk_expander_set_use_underline proto :ptr, :gboolean
gtk_expander_get_use_underline proto :ptr
gtk_expander_set_use_markup proto :ptr, :gboolean
gtk_expander_get_use_markup proto :ptr
gtk_expander_set_label_widget proto :ptr, :ptr
gtk_expander_get_label_widget proto :ptr
gtk_expander_set_resize_toplevel proto :ptr, :gboolean
gtk_expander_get_resize_toplevel proto :ptr
gtk_expander_set_child proto :ptr, :ptr
gtk_expander_get_child proto :ptr

endif

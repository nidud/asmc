ifndef __GTK_CHECK_BUTTON_H__
define __GTK_CHECK_BUTTON_H__


if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktogglebutton.inc

define GTK_TYPE_CHECK_BUTTON <gtk_check_button_get_type ()>
GTK_CHECK_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CHECK_BUTTON, GtkCheckButton))>
  endm
GTK_CHECK_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CHECK_BUTTON, GtkCheckButtonClass))>
  endm
GTK_IS_CHECK_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CHECK_BUTTON))>
  endm
GTK_IS_CHECK_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CHECK_BUTTON))>
  endm
GTK_CHECK_BUTTON_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CHECK_BUTTON, GtkCheckButtonClass))>
  endm


_GtkCheckButton         struct
parent_instance         GtkWidget <>
_GtkCheckButton         ends
GtkCheckButton          typedef _GtkCheckButton

_GtkCheckButtonClass    struct
parent_class            GtkWidgetClass <>
toggled                 proc :ptr
activate                proc :ptr
padding                 gpointer 7 dup(?)
_GtkCheckButtonClass    ends
GtkCheckButtonClass     typedef _GtkCheckButtonClass


gtk_check_button_get_type proto
gtk_check_button_new proto
gtk_check_button_new_with_label proto :ptr
gtk_check_button_new_with_mnemonic proto :ptr
gtk_check_button_set_inconsistent proto :ptr, :gboolean
gtk_check_button_get_inconsistent proto :ptr

gtk_check_button_get_active proto :ptr
gtk_check_button_set_active proto :ptr, :gboolean
gtk_check_button_get_label proto :ptr
gtk_check_button_set_label proto :ptr, :ptr
gtk_check_button_set_group proto :ptr, :ptr
gtk_check_button_get_use_underline proto :ptr
gtk_check_button_set_use_underline proto :ptr, :gboolean

endif

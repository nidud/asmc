ifndef __GTK_BUTTON_H__
define __GTK_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_BUTTON <gtk_button_get_type ()>
GTK_BUTTON macro obj
  exitm<G_TYPE_CHECK_INSTANCE_CAST (obj, GTK_TYPE_BUTTON, GtkButton)>
  endm
GTK_BUTTON_CLASS macro klass
  exitm<G_TYPE_CHECK_CLASS_CAST (klass, GTK_TYPE_BUTTON, GtkButtonClass)>
  endm
GTK_IS_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BUTTON))>
  endm
GTK_IS_BUTTON_CLASS macro klass
  exitm<G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BUTTON)>
  endm
GTK_BUTTON_GET_CLASS macro obj
  exitm<G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BUTTON, GtkButtonClass)>
  endm

GtkButton               struct
parent_instance         GtkWidget <>
GtkButton               ends

GtkButtonClass          struct
parent_class            GtkWidgetClass <>
clicked                 proc :ptr
activate                proc :ptr
padding                 gpointer 8 dup(?)
GtkButtonClass          ends

gtk_button_get_type proto
gtk_button_new proto
gtk_button_new_with_label proto :ptr
gtk_button_new_from_icon_name proto :ptr
gtk_button_new_with_mnemonic proto :ptr

gtk_button_set_has_frame proto :ptr, :gboolean
gtk_button_get_has_frame proto :ptr
gtk_button_set_label proto :ptr, :ptr
gtk_button_get_label proto :ptr
gtk_button_set_use_underline proto :ptr, :gboolean
gtk_button_get_use_underline proto :ptr

gtk_button_set_icon_name proto :ptr, :ptr
gtk_button_get_icon_name proto :ptr

gtk_button_set_child proto :ptr, :ptr
gtk_button_get_child proto :ptr

endif

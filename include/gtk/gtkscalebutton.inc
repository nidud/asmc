ifndef __GTK_SCALE_BUTTON_H__
define __GTK_SCALE_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SCALE_BUTTON <gtk_scale_button_get_type ()>
GTK_SCALE_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButton))>
  endm
GTK_SCALE_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))>
  endm
GTK_IS_SCALE_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCALE_BUTTON))>
  endm
GTK_IS_SCALE_BUTTON_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCALE_BUTTON))>
  endm
GTK_SCALE_BUTTON_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCALE_BUTTON, GtkScaleButtonClass))>
  endm

_GtkScaleButton         struct
parent_instance         GtkWidget <>
_GtkScaleButton         ends
GtkScaleButton          typedef _GtkScaleButton

_GtkScaleButtonClass    struct
parent_class            GtkWidgetClass <>
value_changed           proc :ptr, :real8
padding                 gpointer 8 dup(?)
_GtkScaleButtonClass    ends
GtkScaleButtonClass     typedef _GtkScaleButtonClass

gtk_scale_button_get_type proto
gtk_scale_button_new proto :real8, :real8, :real8, :ptr
gtk_scale_button_set_icons proto :ptr, :ptr
gtk_scale_button_get_value proto :ptr
gtk_scale_button_set_value proto :ptr, :real8
gtk_scale_button_get_adjustment proto :ptr
gtk_scale_button_set_adjustment proto :ptr, :ptr
gtk_scale_button_get_plus_button proto :ptr
gtk_scale_button_get_minus_button proto :ptr
gtk_scale_button_get_popup proto :ptr

endif

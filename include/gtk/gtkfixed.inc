ifndef __GTK_FIXED_H__
define __GTK_FIXED_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_FIXED <gtk_fixed_get_type>
GTK_FIXED macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FIXED, GtkFixed))>
  endm
GTK_FIXED_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_FIXED, GtkFixedClass))>
  endm
GTK_IS_FIXED macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FIXED))>
  endm
GTK_IS_FIXED_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_FIXED))>
  endm
GTK_FIXED_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_FIXED, GtkFixedClass))>
  endm

_GtkFixed               struct
parent_instance         GtkWidget <>
_GtkFixed               ends
GtkFixed                typedef _GtkFixed

_GtkFixedClass          struct
parent_class            GtkWidgetClass <>
padding                 gpointer 8 dup(?)
_GtkFixedClass          ends
GtkFixedClass           typedef _GtkFixedClass

gtk_fixed_get_type proto

gtk_fixed_new proto
gtk_fixed_put proto :ptr, :ptr, :real8, :real8
gtk_fixed_remove proto :ptr, :ptr
gtk_fixed_move proto :ptr, :ptr, :real8, :real8
gtk_fixed_get_child_position proto :ptr, :ptr, :ptr, :ptr

gtk_fixed_set_child_transform proto :ptr, :ptr, :ptr
gtk_fixed_get_child_transform proto :ptr, :ptr

endif

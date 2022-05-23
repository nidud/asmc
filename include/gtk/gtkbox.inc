ifndef __GTK_BOX_H__
define __GTK_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_BOX <gtk_box_get_type>
GTK_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_BOX, GtkBox))>
  endm
GTK_BOX_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_BOX, GtkBoxClass))>
  endm
GTK_IS_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_BOX))>
  endm
GTK_IS_BOX_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_BOX))>
  endm
GTK_BOX_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_BOX, GtkBoxClass))>
  endm

_GtkBox                 struct
parent_instance         GtkWidget <>
_GtkBox                 ends
GtkBox                  typedef _GtkBox

_GtkBoxClass            struct
parent_class            GtkWidgetClass <>
padding                 gpointer 8 dup(?)
_GtkBoxClass            ends
GtkBoxClass             typedef _GtkBoxClass


gtk_box_get_type proto
gtk_box_new proto :GtkOrientation, :sdword
gtk_box_set_homogeneous proto :ptr, :gboolean
gtk_box_get_homogeneous proto :ptr
gtk_box_set_spacing proto :ptr, :sdword
gtk_box_get_spacing proto :ptr
gtk_box_set_baseline_position proto :ptr, :GtkBaselinePosition
gtk_box_get_baseline_position proto :ptr

gtk_box_append proto :ptr, :ptr
gtk_box_prepend proto :ptr, :ptr
gtk_box_remove proto :ptr, :ptr

gtk_box_insert_child_after proto :ptr, :ptr, :ptr
gtk_box_reorder_child_after proto :ptr, :ptr, :ptr

endif

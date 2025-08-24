ifndef __GTK_CENTER_BOX_H__
define __GTK_CENTER_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtkwidget.inc

define GTK_TYPE_CENTER_BOX <gtk_center_box_get_type ()>
GTK_CENTER_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CENTER_BOX, GtkCenterBox))>
  endm
GTK_CENTER_BOX_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CENTER_BOX, GtkCenterBoxClass))>
  endm
GTK_IS_CENTER_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CENTER_BOX))>
  endm
GTK_IS_CENTER_BOX_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CENTER_BOX))>
  endm
GTK_CENTER_BOX_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CENTER_BOX, GtkCenterBoxClass))>
  endm

gtk_center_box_get_type proto

gtk_center_box_new proto
gtk_center_box_set_start_widget proto :ptr, :ptr
gtk_center_box_set_center_widget proto :ptr, :ptr
gtk_center_box_set_end_widget proto :ptr, :ptr

gtk_center_box_get_start_widget proto :ptr
gtk_center_box_get_center_widget proto :ptr
gtk_center_box_get_end_widget proto :ptr

gtk_center_box_set_baseline_position proto :ptr, :GtkBaselinePosition
gtk_center_box_get_baseline_position proto :ptr

endif

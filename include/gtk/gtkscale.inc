ifndef __GTK_SCALE_H__
define __GTK_SCALE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkrange.inc

define GTK_TYPE_SCALE <gtk_scale_get_type ()>
GTK_SCALE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SCALE, GtkScale))>
  endm
GTK_SCALE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SCALE, GtkScaleClass))>
  endm
GTK_IS_SCALE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SCALE))>
  endm
GTK_IS_SCALE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SCALE))>
  endm
GTK_SCALE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SCALE, GtkScaleClass))>
  endm

GtkScale                struct
parent_instance         GtkRange <>
GtkScale                ends

GtkScaleClass           struct
parent_class            GtkRangeClass <>
get_layout_offsets      proc :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
GtkScaleClass           ends

CALLBACK(GtkScaleFormatValueFunc, :ptr, :real8, :gpointer)

gtk_scale_get_type proto
gtk_scale_new proto :GtkOrientation, :ptr
gtk_scale_new_with_range proto :GtkOrientation, :real8, :real8, :real8
gtk_scale_set_digits proto :ptr, :sdword
gtk_scale_get_digits proto :ptr
gtk_scale_set_draw_value proto :ptr, :gboolean
gtk_scale_get_draw_value proto :ptr
gtk_scale_set_has_origin proto :ptr, :gboolean
gtk_scale_get_has_origin proto :ptr
gtk_scale_set_value_pos proto :ptr, :GtkPositionType
gtk_scale_get_value_pos proto :ptr

gtk_scale_get_layout proto :ptr
gtk_scale_get_layout_offsets proto :ptr, :ptr, :ptr

gtk_scale_add_mark proto :ptr, :real8, :GtkPositionType, :ptr
gtk_scale_clear_marks proto :ptr

gtk_scale_set_format_value_func proto :ptr, :GtkScaleFormatValueFunc, :gpointer, :GDestroyNotify

endif

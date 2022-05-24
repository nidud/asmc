ifndef __GTK_RANGE_H__
define __GTK_RANGE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_RANGE <gtk_range_get_type ()>
GTK_RANGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RANGE, GtkRange))>
  endm
GTK_RANGE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RANGE, GtkRangeClass))>
  endm
GTK_IS_RANGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RANGE))>
  endm
GTK_IS_RANGE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RANGE))>
  endm
GTK_RANGE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RANGE, GtkRangeClass))>
  endm

_GtkRange               struct
parent_instance         GtkWidget <>
_GtkRange               ends
GtkRange                typedef _GtkRange

_GtkRangeClass          struct
parent_class            GtkWidgetClass <>
value_changed           proc :ptr
adjust_bounds           proc :ptr, :real8
move_slider             proc :ptr, :GtkScrollType
get_range_border        proc :ptr, :ptr
change_value            proc :ptr, :GtkScrollType, :real8
padding                 gpointer 8 dup(?)
_GtkRangeClass          ends
GtkRangeClass           typedef _GtkRangeClass


gtk_range_get_type proto
gtk_range_set_adjustment proto :ptr, :ptr
gtk_range_get_adjustment proto :ptr
gtk_range_set_inverted proto :ptr, :gboolean
gtk_range_get_inverted proto :ptr
gtk_range_set_flippable proto :ptr, :gboolean
gtk_range_get_flippable proto :ptr
gtk_range_set_slider_size_fixed proto :ptr, :gboolean
gtk_range_get_slider_size_fixed proto :ptr
gtk_range_get_range_rect proto :ptr, :ptr
gtk_range_get_slider_range proto :ptr, :ptr, :ptr
gtk_range_set_increments proto :ptr, :real8, :real8
gtk_range_set_range proto :ptr, :real8, :real8
gtk_range_set_value proto :ptr, :real8
gtk_range_get_value proto :ptr

gtk_range_set_show_fill_level proto :ptr, :gboolean
gtk_range_get_show_fill_level proto :ptr
gtk_range_set_restrict_to_fill_level proto :ptr, :gboolean
gtk_range_get_restrict_to_fill_level proto :ptr
gtk_range_set_fill_level proto :ptr, :real8
gtk_range_get_fill_level proto :ptr
gtk_range_set_round_digits proto :ptr, :sdword
gtk_range_get_round_digits proto :ptr

endif

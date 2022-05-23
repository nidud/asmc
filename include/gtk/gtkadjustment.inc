ifndef __GTK_ADJUSTMENT_H__
define __GTK_ADJUSTMENT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc

define GTK_TYPE_ADJUSTMENT                  <gtk_adjustment_get_type>
GTK_ADJUSTMENT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustment))>
  endm
GTK_ADJUSTMENT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))>
  endm
GTK_IS_ADJUSTMENT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ADJUSTMENT))>
  endm
GTK_IS_ADJUSTMENT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ADJUSTMENT))>
  endm
GTK_ADJUSTMENT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ADJUSTMENT, GtkAdjustmentClass))>
  endm


_GtkAdjustment          struct
parent_instance         GInitiallyUnowned <>
_GtkAdjustment          ends

_GtkAdjustmentClass     struct
parent_class            GInitiallyUnownedClass <>
changed                 proc :ptr
value_changed           proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_GtkAdjustmentClass     ends
GtkAdjustmentClass      typedef _GtkAdjustmentClass


gtk_adjustment_get_type proto
gtk_adjustment_new proto :real8, :real8, :real8, :real8, :real8, :real8

gtk_adjustment_clamp_page proto :ptr, :real8, :real8

gtk_adjustment_get_value proto :ptr
gtk_adjustment_set_value proto :ptr, :real8
gtk_adjustment_get_lower proto :ptr
gtk_adjustment_set_lower proto :ptr, :real8
gtk_adjustment_get_upper proto :ptr
gtk_adjustment_set_upper proto :ptr, :real8
gtk_adjustment_get_step_increment proto :ptr
gtk_adjustment_set_step_increment proto :ptr, :real8
gtk_adjustment_get_page_increment proto :ptr
gtk_adjustment_set_page_increment proto :ptr, :real8
gtk_adjustment_get_page_size proto :ptr
gtk_adjustment_set_page_size proto :ptr, :real8

gtk_adjustment_configure proto :ptr, :real8, :real8, :real8, :real8, :real8, :real8
gtk_adjustment_get_minimum_increment proto :ptr

endif

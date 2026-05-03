ifndef __GTK_POPOVER_H__
define __GTK_POPOVER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_POPOVER <gtk_popover_get_type ()>
GTK_POPOVER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_POPOVER, GtkPopover))>
  endm
GTK_POPOVER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_POPOVER, GtkPopoverClass))>
  endm
GTK_IS_POPOVER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_POPOVER))>
  endm
GTK_IS_POPOVER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_POPOVER))>
  endm
GTK_POPOVER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_POPOVER, GtkPopoverClass))>
  endm

GtkPopover              struct
parent                  GtkWidget <>
GtkPopover              ends

GtkPopoverClass         struct
parent_class            GtkWidgetClass <>
closed                  proc :ptr
activate_default        proc :ptr
reserved                gpointer 8 dup(?)
GtkPopoverClass         ends

gtk_popover_get_type proto
gtk_popover_new proto
gtk_popover_set_child proto :ptr, :ptr
gtk_popover_get_child proto :ptr
gtk_popover_set_pointing_to proto :ptr, :ptr
gtk_popover_get_pointing_to proto :ptr, :ptr
gtk_popover_set_position proto :ptr, :GtkPositionType
gtk_popover_get_position proto :ptr
gtk_popover_set_autohide proto :ptr, :gboolean
gtk_popover_get_autohide proto :ptr
gtk_popover_set_has_arrow proto :ptr, :gboolean
gtk_popover_get_has_arrow proto :ptr
gtk_popover_set_mnemonics_visible proto :ptr, :gboolean
gtk_popover_get_mnemonics_visible proto :ptr
gtk_popover_popup proto :ptr
gtk_popover_popdown proto :ptr
gtk_popover_set_offset proto :ptr, :sdword, :sdword
gtk_popover_get_offset proto :ptr, :ptr, :ptr
gtk_popover_set_cascade_popdown proto :ptr, :gboolean
gtk_popover_get_cascade_popdown proto :ptr
gtk_popover_set_default_widget proto :ptr, :ptr
gtk_popover_present proto :ptr

endif

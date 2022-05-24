ifndef __GTK_COLOR_CHOOSER_H__
define __GTK_COLOR_CHOOSER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_COLOR_CHOOSER <gtk_color_chooser_get_type ()>
GTK_COLOR_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COLOR_CHOOSER, GtkColorChooser))>
  endm
GTK_IS_COLOR_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COLOR_CHOOSER))>
  endm
GTK_COLOR_CHOOSER_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_COLOR_CHOOSER, GtkColorChooserInterface))>
  endm

;GtkColorChooser         typedef _GtkColorChooser

_GtkColorChooserInterface struct
base_interface          GTypeInterface <>
get_rgba                proc :ptr, :ptr
set_rgba                proc :ptr, :ptr
add_palette             proc :ptr, :GtkOrientation, :sdword, :sdword, :ptr
color_activated         proc :ptr, :ptr
padding                 gpointer 12 dup(?)
_GtkColorChooserInterface ends
GtkColorChooserInterface typedef _GtkColorChooserInterface

gtk_color_chooser_get_type proto
gtk_color_chooser_get_rgba proto :ptr, :ptr
gtk_color_chooser_set_rgba proto :ptr, :ptr
gtk_color_chooser_get_use_alpha proto :ptr
gtk_color_chooser_set_use_alpha proto :ptr, :gboolean
gtk_color_chooser_add_palette proto :ptr, :GtkOrientation, :sdword, :sdword, :ptr

endif

ifndef __GTK_TOOLTIP_H__
define __GTK_TOOLTIP_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

define GTK_TYPE_TOOLTIP <gtk_tooltip_get_type ()>
GTK_TOOLTIP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOOLTIP, GtkTooltip))>
  endm
GTK_IS_TOOLTIP macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOOLTIP))>
  endm

gtk_tooltip_get_type proto
gtk_tooltip_set_markup proto :ptr, :ptr
gtk_tooltip_set_text proto :ptr, :ptr
gtk_tooltip_set_icon proto :ptr, :ptr
gtk_tooltip_set_icon_from_icon_name proto :ptr, :ptr
gtk_tooltip_set_icon_from_gicon proto :ptr, :ptr
gtk_tooltip_set_custom proto :ptr, :ptr
gtk_tooltip_set_tip_area proto :ptr, :ptr

endif

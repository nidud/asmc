ifndef __GTK_COLOR_BUTTON_H__
define __GTK_COLOR_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

define GTK_TYPE_COLOR_BUTTON <gtk_color_button_get_type ()>
GTK_COLOR_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COLOR_BUTTON, GtkColorButton))>
  endm
GTK_IS_COLOR_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COLOR_BUTTON))>
  endm

;GtkColorButton          typedef _GtkColorButton

gtk_color_button_get_type proto
gtk_color_button_new proto
gtk_color_button_new_with_rgba proto :ptr
gtk_color_button_set_title proto :ptr, :ptr
gtk_color_button_get_title proto :ptr
gtk_color_button_get_modal proto :ptr
gtk_color_button_set_modal proto :ptr, :gboolean

endif

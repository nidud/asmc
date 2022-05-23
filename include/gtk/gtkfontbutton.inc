ifndef __GTK_FONT_BUTTON_H__
define __GTK_FONT_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkbutton.inc

define GTK_TYPE_FONT_BUTTON <gtk_font_button_get_type>
GTK_FONT_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_BUTTON, GtkFontButton))>
  endm
GTK_IS_FONT_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_BUTTON))>
  endm

;GtkFontButton           typedef _GtkFontButton

gtk_font_button_get_type proto
gtk_font_button_new proto
gtk_font_button_new_with_font proto :ptr
gtk_font_button_get_title proto :ptr
gtk_font_button_set_title proto :ptr, :ptr
gtk_font_button_get_modal proto :ptr
gtk_font_button_set_modal proto :ptr, :gboolean
gtk_font_button_get_use_font proto :ptr
gtk_font_button_set_use_font proto :ptr, :gboolean
gtk_font_button_get_use_size proto :ptr
gtk_font_button_set_use_size proto :ptr, :gboolean

endif

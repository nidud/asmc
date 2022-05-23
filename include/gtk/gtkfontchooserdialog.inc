ifndef __GTK_FONT_CHOOSER_DIALOG_H__
define __GTK_FONT_CHOOSER_DIALOG_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkdialog.inc

define GTK_TYPE_FONT_CHOOSER_DIALOG <gtk_font_chooser_dialog_get_type>
GTK_FONT_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_CHOOSER_DIALOG, GtkFontChooserDialog))>
  endm
GTK_IS_FONT_CHOOSER_DIALOG macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_CHOOSER_DIALOG))>
  endm

;GtkFontChooserDialog    typedef _GtkFontChooserDialog

gtk_font_chooser_dialog_get_type proto
gtk_font_chooser_dialog_new proto :ptr, :ptr

endif

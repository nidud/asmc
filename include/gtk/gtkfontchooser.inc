ifndef __GTK_FONT_CHOOSER_H__
define __GTK_FONT_CHOOSER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

CALLBACK(GtkFontFilterFunc, :ptr, :ptr, :gpointer)

.enum GtkFontChooserLevel {
  GTK_FONT_CHOOSER_LEVEL_FAMILY	    = 0,
  GTK_FONT_CHOOSER_LEVEL_STYLE	    = 1 shl 0,
  GTK_FONT_CHOOSER_LEVEL_SIZE	    = 1 shl 1,
  GTK_FONT_CHOOSER_LEVEL_VARIATIONS = 1 shl 2,
  GTK_FONT_CHOOSER_LEVEL_FEATURES   = 1 shl 3
}

define GTK_TYPE_FONT_CHOOSER <gtk_font_chooser_get_type>
GTK_FONT_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_CHOOSER, GtkFontChooser))>
  endm
GTK_IS_FONT_CHOOSER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_CHOOSER))>
  endm
GTK_FONT_CHOOSER_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_FONT_CHOOSER, GtkFontChooserIface))>
  endm

;GtkFontChooser		 typedef _GtkFontChooser

_GtkFontChooserIface	struct
base_iface		GTypeInterface <>
get_font_family		proc :ptr
get_font_face		proc :ptr
get_font_size		proc :ptr
set_filter_func		proc :ptr, :GtkFontFilterFunc, :gpointer, :GDestroyNotify
font_activated		proc :ptr, :ptr
set_font_map		proc :ptr, :ptr
get_font_map		proc :ptr
padding			gpointer 10 dup(?)
_GtkFontChooserIface	ends
GtkFontChooserIface	typedef _GtkFontChooserIface

gtk_font_chooser_get_type proto
gtk_font_chooser_get_font_family proto :ptr
gtk_font_chooser_get_font_face proto :ptr
gtk_font_chooser_get_font_size proto :ptr
gtk_font_chooser_get_font_desc proto :ptr
gtk_font_chooser_set_font_desc proto :ptr, :ptr
gtk_font_chooser_get_font proto :ptr
gtk_font_chooser_set_font proto :ptr, :ptr
gtk_font_chooser_get_preview_text proto :ptr
gtk_font_chooser_set_preview_text proto :ptr, :ptr
gtk_font_chooser_get_show_preview_entry proto :ptr
gtk_font_chooser_set_show_preview_entry proto :ptr, :gboolean
gtk_font_chooser_set_filter_func proto :ptr, :GtkFontFilterFunc, :gpointer, :GDestroyNotify
gtk_font_chooser_set_font_map proto :ptr, :ptr
gtk_font_chooser_get_font_map proto :ptr
gtk_font_chooser_set_level proto :ptr, :GtkFontChooserLevel
gtk_font_chooser_get_level proto :ptr
gtk_font_chooser_get_font_features proto :ptr
gtk_font_chooser_get_language proto :ptr
gtk_font_chooser_set_language proto :ptr, :ptr

endif

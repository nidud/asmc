ifndef __GTK_FONT_CHOOSER_H__
__GTK_FONT_CHOOSER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

CALLBACKC(GtkFontFilterFunc, :ptr PangoFontFamily, :ptr PangoFontFace, :gpointer)

GTK_TYPE_FONT_CHOOSER equ <gtk_font_chooser_get_type>
GTK_FONT_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FONT_CHOOSER, GtkFontChooser))>
	endm
GTK_IS_FONT_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FONT_CHOOSER))>
	endm
GTK_FONT_CHOOSER_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_FONT_CHOOSER, GtkFontChooserIface))>
	endm

GtkFontChooserIface	STRUC
base_iface		GTypeInterface <>
get_font_family		proc :ptr GtkFontChooser
get_font_face		proc :ptr GtkFontChooser
get_font_size		proc :ptr GtkFontChooser
set_filter_func		proc :ptr GtkFontChooser, :GtkFontFilterFunc, :gpointer, :GDestroyNotify
font_activated		proc :ptr GtkFontChooser, :ptr gchar
set_font_map		proc :ptr GtkFontChooser, :ptr PangoFontMap
get_font_map		proc :ptr GtkFontChooser
padding			gpointer 10 dup(?)
GtkFontChooserIface	ENDS

;GType
gtk_font_chooser_get_type proto __cdecl

;PangoFontFamily
gtk_font_chooser_get_font_family proto __cdecl \
	   fontchooser: ptr GtkFontChooser

;PangoFontFace
gtk_font_chooser_get_font_face proto __cdecl \
	   fontchooser: ptr GtkFontChooser

;gint
gtk_font_chooser_get_font_size proto __cdecl \
	   fontchooser: ptr GtkFontChooser


;PangoFontDescription
gtk_font_chooser_get_font_desc proto __cdecl \
	   fontchooser: ptr GtkFontChooser

;void
gtk_font_chooser_set_font_desc proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
	     font_desc: ptr PangoFontDescription


;gchar*
gtk_font_chooser_get_font proto __cdecl \
	   fontchooser: ptr GtkFontChooser


;void
gtk_font_chooser_set_font proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
	      fontname: ptr gchar

;gchar*
gtk_font_chooser_get_preview_text proto __cdecl \
	   fontchooser: ptr GtkFontChooser

;void
gtk_font_chooser_set_preview_text proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
		  text: ptr gchar

;gboolean
gtk_font_chooser_get_show_preview_entry proto __cdecl \
	   fontchooser: ptr GtkFontChooser

;void
gtk_font_chooser_set_show_preview_entry proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
    show_preview_entry: gboolean

;void
gtk_font_chooser_set_filter_func proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
		filter: GtkFontFilterFunc,
	     user_data: gpointer,
	       destroy: GDestroyNotify

;void
gtk_font_chooser_set_font_map proto __cdecl \
	   fontchooser: ptr GtkFontChooser,
	       fontmap: ptr PangoFontMap

;PangoFontMap
gtk_font_chooser_get_font_map proto __cdecl \
	   fontchooser: ptr GtkFontChooser

G_END_DECLS

endif

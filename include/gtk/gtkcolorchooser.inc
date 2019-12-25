ifndef __GTK_COLOR_CHOOSER_H__
__GTK_COLOR_CHOOSER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

G_BEGIN_DECLS

GTK_TYPE_COLOR_CHOOSER	equ <gtk_color_chooser_get_type>
GTK_COLOR_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_COLOR_CHOOSER, GtkColorChooser))>
	endm
GTK_IS_COLOR_CHOOSER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_COLOR_CHOOSER))>
	endm
GTK_COLOR_CHOOSER_GET_IFACE macro inst
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_COLOR_CHOOSER, GtkColorChooserInterface))>
	endm

GtkColorChooserInterface STRUC
base_interface		GTypeInterface <>
get_rgba		proc :ptr GtkColorChooser, :ptr GdkRGBA
set_rgba		proc :ptr GtkColorChooser, :ptr GdkRGBA
add_palette		proc :ptr GtkColorChooser, :GtkOrientation, :gint, :gint, :ptr GdkRGBA
color_activated		proc :ptr GtkColorChooser, :ptr GdkRGBA
padding			gpointer 12 dup(?)
GtkColorChooserInterface ENDS

;GType
gtk_color_chooser_get_type proto __cdecl

;void
gtk_color_chooser_get_rgba proto __cdecl \
	       chooser: ptr GtkColorChooser,
		 color: ptr GdkRGBA

;void
gtk_color_chooser_set_rgba proto __cdecl \
	       chooser: ptr GtkColorChooser,
		 color: ptr GdkRGBA

;gboolean
gtk_color_chooser_get_use_alpha proto __cdecl \
	       chooser: ptr GtkColorChooser


;void
gtk_color_chooser_set_use_alpha proto __cdecl \
	       chooser: ptr GtkColorChooser,
	     use_alpha: gboolean


;void
gtk_color_chooser_add_palette proto __cdecl \
	       chooser: ptr GtkColorChooser,
	   orientation: GtkOrientation,
       colors_per_line: gint,
	      n_colors: gint,
		colors: ptr GdkRGBA

G_END_DECLS

endif

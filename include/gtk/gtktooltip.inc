ifndef __GTK_TOOLTIP_H__
__GTK_TOOLTIP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwindow.inc

G_BEGIN_DECLS

GTK_TYPE_TOOLTIP equ <gtk_tooltip_get_type>
GTK_TOOLTIP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_TOOLTIP, GtkTooltip))>
	endm
GTK_IS_TOOLTIP macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_TOOLTIP))>
	endm

;GType
gtk_tooltip_get_type proto __cdecl

;void
gtk_tooltip_set_markup proto __cdecl \
	       tooltip: ptr GtkTooltip,
		markup: ptr gchar

;void
gtk_tooltip_set_text proto __cdecl \
	       tooltip: ptr GtkTooltip,
		  text: ptr gchar

;void
gtk_tooltip_set_icon proto __cdecl \
	       tooltip: ptr GtkTooltip,
		pixbuf: ptr GdkPixbuf

;void
gtk_tooltip_set_icon_from_stock proto __cdecl \
	       tooltip: ptr GtkTooltip,
	      stock_id: ptr gchar,
		  size: GtkIconSize

;void
gtk_tooltip_set_icon_from_icon_name proto __cdecl \
	       tooltip: ptr GtkTooltip,
	     icon_name: ptr gchar,
		  size: GtkIconSize

;void
gtk_tooltip_set_icon_from_gicon proto __cdecl \
	       tooltip: ptr GtkTooltip,
		 gicon: ptr GIcon,
		  size: GtkIconSize

;void
gtk_tooltip_set_custom proto __cdecl \
	       tooltip: ptr GtkTooltip,
	 custom_widget: ptr GtkWidget


;void
gtk_tooltip_set_tip_area proto __cdecl \
	       tooltip: ptr GtkTooltip,
		  rect: ptr GdkRectangle


;void
gtk_tooltip_trigger_tooltip_query proto __cdecl \
	       display: ptr GdkDisplay


G_END_DECLS

endif

ifndef __GTK_CELL_VIEW_H__
__GTK_CELL_VIEW_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc
include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtkcellareacontext.inc
include gtk/gtktreemodel.inc

G_BEGIN_DECLS

GTK_TYPE_CELL_VIEW equ <gtk_cell_view_get_type>
GTK_CELL_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_VIEW, GtkCellView))>
	endm
GTK_CELL_VIEW_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_CAST ((vtable), GTK_TYPE_CELL_VIEW, GtkCellViewClass))>
	endm
GTK_IS_CELL_VIEW macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_VIEW))>
	endm
GTK_IS_CELL_VIEW_CLASS macro vtable
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((vtable), GTK_TYPE_CELL_VIEW))>
	endm
GTK_CELL_VIEW_GET_CLASS macro inst
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((inst), GTK_TYPE_CELL_VIEW, GtkCellViewClass))>
	endm

GtkCellView		STRUC
parent_instance		GtkWidget <>
priv			ptr_t ?
GtkCellView		ENDS

GtkCellViewClass	STRUC
parent_class		GtkWidgetClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCellViewClass	ENDS

;GType
gtk_cell_view_get_type proto __cdecl
;GtkWidget
gtk_cell_view_new proto __cdecl
;GtkWidget
gtk_cell_view_new_with_context proto __cdecl \
		  area: ptr GtkCellArea,
	       context: ptr GtkCellAreaContext

;GtkWidget
gtk_cell_view_new_with_text proto __cdecl \
		  text: ptr gchar

;GtkWidget
gtk_cell_view_new_with_markup proto __cdecl \
		markup: ptr gchar

;GtkWidget
gtk_cell_view_new_with_pixbuf proto __cdecl \
		pixbuf: ptr GdkPixbuf

;void
gtk_cell_view_set_model proto __cdecl \
	     cell_view: ptr GtkCellView,
		 model: ptr GtkTreeModel

;GtkTreeModel
gtk_cell_view_get_model proto __cdecl \
	     cell_view: ptr GtkCellView

;void
gtk_cell_view_set_displayed_row proto __cdecl \
	     cell_view: ptr GtkCellView,
		  path: ptr GtkTreePath

;GtkTreePath
gtk_cell_view_get_displayed_row proto __cdecl \
	     cell_view: ptr GtkCellView

;void
gtk_cell_view_set_background_rgba proto __cdecl \
	     cell_view: ptr GtkCellView,
		  rgba: ptr GdkRGBA

;gboolean
gtk_cell_view_get_draw_sensitive proto __cdecl \
	     cell_view: ptr GtkCellView

;void
gtk_cell_view_set_draw_sensitive proto __cdecl \
	     cell_view: ptr GtkCellView,
	draw_sensitive: gboolean

;gboolean
gtk_cell_view_get_fit_model proto __cdecl \
	     cell_view: ptr GtkCellView

;void
gtk_cell_view_set_fit_model proto __cdecl \
	     cell_view: ptr GtkCellView,
	     fit_model: gboolean


;gboolean
gtk_cell_view_get_size_of_row proto __cdecl \
	     cell_view: ptr GtkCellView,
		  path: ptr GtkTreePath,
	   requisition: ptr GtkRequisition

;void
gtk_cell_view_set_background_color proto __cdecl \
	     cell_view: ptr GtkCellView,
		 color: ptr GdkColor

G_END_DECLS

endif

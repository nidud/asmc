ifndef __GTK_DRAWING_AREA_H__
define __GTK_DRAWING_AREA_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_DRAWING_AREA <gtk_drawing_area_get_type ()>
GTK_DRAWING_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_DRAWING_AREA, GtkDrawingArea))>
  endm
GTK_DRAWING_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_DRAWING_AREA, GtkDrawingAreaClass))>
  endm
GTK_IS_DRAWING_AREA macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_DRAWING_AREA))>
  endm
GTK_IS_DRAWING_AREA_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_DRAWING_AREA))>
  endm
GTK_DRAWING_AREA_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_DRAWING_AREA, GtkDrawingAreaClass))>
  endm

CALLBACK(GtkDrawingAreaDrawFunc, :ptr, :ptr, :sdword, :sdword, :gpointer)

GtkDrawingArea          struct
widget                  GtkWidget <>
GtkDrawingArea          ends

GtkDrawingAreaClass     struct
parent_class            GtkWidgetClass <>
resize                  proc :ptr, :sdword, :sdword
padding                 gpointer 8 dup(?)
GtkDrawingAreaClass     ends

gtk_drawing_area_get_type proto
gtk_drawing_area_new proto
gtk_drawing_area_set_content_width proto :ptr, :sdword
gtk_drawing_area_get_content_width proto :ptr
gtk_drawing_area_set_content_height proto :ptr, :sdword
gtk_drawing_area_get_content_height proto :ptr
gtk_drawing_area_set_draw_func proto :ptr, :GtkDrawingAreaDrawFunc, :gpointer, :GDestroyNotify

endif

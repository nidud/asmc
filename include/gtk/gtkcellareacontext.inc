ifndef __GTK_CELL_AREA_CONTEXT_H__
define __GTK_CELL_AREA_CONTEXT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellarea.inc

define GTK_TYPE_CELL_AREA_CONTEXT            <gtk_cell_area_context_get_type>
GTK_CELL_AREA_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContext))>
  endm
GTK_CELL_AREA_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContextClass))>
  endm
GTK_IS_CELL_AREA_CONTEXT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA_CONTEXT))>
  endm
GTK_IS_CELL_AREA_CONTEXT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_CELL_AREA_CONTEXT))>
  endm
GTK_CELL_AREA_CONTEXT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_CELL_AREA_CONTEXT, GtkCellAreaContextClass))>
  endm

;GtkCellAreaContextPrivate typedef _GtkCellAreaContextPrivate

_GtkCellAreaContext     struct
parent_instance         GObject <>
_GtkCellAreaContext     ends

_GtkCellAreaContextClass struct
parent_class            GObjectClass <>
allocate                proc :ptr, :sdword, :sdword
reset                   proc :ptr
get_preferred_height_for_width proc :ptr, :sdword, :ptr, :ptr
get_preferred_width_for_height proc :ptr, :sdword, :ptr, :ptr
padding                 gpointer 8 dup(?)
_GtkCellAreaContextClass ends
GtkCellAreaContextClass typedef _GtkCellAreaContextClass

gtk_cell_area_context_get_type proto

gtk_cell_area_context_get_area proto :ptr
gtk_cell_area_context_allocate proto :ptr, :sdword, :sdword
gtk_cell_area_context_reset proto :ptr

gtk_cell_area_context_get_preferred_width proto :ptr, :ptr, :ptr
gtk_cell_area_context_get_preferred_height proto :ptr, :ptr, :ptr
gtk_cell_area_context_get_preferred_height_for_width proto :ptr, :sdword, :ptr, :ptr
gtk_cell_area_context_get_preferred_width_for_height proto :ptr, :sdword, :ptr, :ptr
gtk_cell_area_context_get_allocation proto :ptr, :ptr, :ptr

gtk_cell_area_context_push_preferred_width proto :ptr, :sdword, :sdword
gtk_cell_area_context_push_preferred_height proto :ptr, :sdword, :sdword

endif

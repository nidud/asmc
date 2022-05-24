ifndef __GTK_CELL_AREA_BOX_H__
define __GTK_CELL_AREA_BOX_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellarea.inc

define GTK_TYPE_CELL_AREA_BOX <gtk_cell_area_box_get_type ()>
GTK_CELL_AREA_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_AREA_BOX, GtkCellAreaBox))>
  endm
GTK_IS_CELL_AREA_BOX macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_AREA_BOX))>
  endm

;GtkCellAreaBox          typedef _GtkCellAreaBox

gtk_cell_area_box_get_type proto
gtk_cell_area_box_new proto
gtk_cell_area_box_pack_start proto :ptr, :ptr, :gboolean, :gboolean, :gboolean
gtk_cell_area_box_pack_end proto :ptr, :ptr, :gboolean, :gboolean, :gboolean
gtk_cell_area_box_get_spacing proto :ptr
gtk_cell_area_box_set_spacing proto :ptr, :sdword

_gtk_cell_area_box_group_visible proto :ptr, :sdword

endif

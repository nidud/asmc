ifndef __GTK_CELL_LAYOUT_H__
define __GTK_CELL_LAYOUT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderer.inc
include gtk/gtkcellarea.inc
include gtk/gtkbuildable.inc
include gtk/gtkbuilder.inc

define GTK_TYPE_CELL_LAYOUT <gtk_cell_layout_get_type ()>
GTK_CELL_LAYOUT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_LAYOUT, GtkCellLayout))>
  endm
GTK_IS_CELL_LAYOUT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_LAYOUT))>
  endm
GTK_CELL_LAYOUT_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GTK_TYPE_CELL_LAYOUT, GtkCellLayoutIface))>
  endm

;GtkCellLayout           typedef _GtkCellLayout

CALLBACK(GtkCellLayoutDataFunc, :ptr, :ptr, :ptr, :ptr, :gpointer)

_GtkCellLayoutIface     struct
g_iface                 GTypeInterface <>
pack_start              proc :ptr, :ptr, :gboolean
pack_end                proc :ptr, :ptr, :gboolean
clear                   proc :ptr
add_attribute           proc :ptr, :ptr, :ptr, :sdword
set_cell_data_func      proc :ptr, :ptr, :GtkCellLayoutDataFunc, :gpointer, :GDestroyNotify
clear_attributes        proc :ptr, :ptr
reorder                 proc :ptr, :ptr, :sdword
get_cells               proc :ptr
get_area                proc :ptr
_GtkCellLayoutIface     ends
GtkCellLayoutIface      typedef _GtkCellLayoutIface

gtk_cell_layout_get_type proto
gtk_cell_layout_pack_start proto :ptr, :ptr, :gboolean
gtk_cell_layout_pack_end proto :ptr, :ptr, :gboolean
gtk_cell_layout_get_cells proto :ptr
gtk_cell_layout_clear proto :ptr
gtk_cell_layout_set_attributes proto :ptr, :ptr, :vararg
gtk_cell_layout_add_attribute proto :ptr, :ptr, :ptr, :sdword
gtk_cell_layout_set_cell_data_func proto :ptr, :ptr, :GtkCellLayoutDataFunc, :gpointer, :GDestroyNotify
gtk_cell_layout_clear_attributes proto :ptr, :ptr
gtk_cell_layout_reorder proto :ptr, :ptr, :sdword
gtk_cell_layout_get_area proto :ptr

_gtk_cell_layout_buildable_custom_tag_start proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
_gtk_cell_layout_buildable_custom_tag_end proto :ptr, :ptr, :ptr, :ptr, :ptr
_gtk_cell_layout_buildable_add_child proto :ptr, :ptr, :ptr, :ptr

endif

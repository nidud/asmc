ifndef __GTK_CELL_RENDERER_ACCEL_H__
define __GTK_CELL_RENDERER_ACCEL_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkcellrenderertext.inc

define GTK_TYPE_CELL_RENDERER_ACCEL            <gtk_cell_renderer_accel_get_type>
GTK_CELL_RENDERER_ACCEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_CELL_RENDERER_ACCEL, GtkCellRendererAccel))>
  endm
GTK_IS_CELL_RENDERER_ACCEL macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_CELL_RENDERER_ACCEL))>
  endm

;GtkCellRendererAccel    typedef _GtkCellRendererAccel

.enum GtkCellRendererAccelMode {
  GTK_CELL_RENDERER_ACCEL_MODE_GTK,
  GTK_CELL_RENDERER_ACCEL_MODE_OTHER
}

gtk_cell_renderer_accel_get_type proto
gtk_cell_renderer_accel_new proto

endif

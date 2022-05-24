ifndef __GTK_OVERLAY_H__
define __GTK_OVERLAY_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_OVERLAY <gtk_overlay_get_type ()>
GTK_OVERLAY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_OVERLAY, GtkOverlay))>
  endm
GTK_IS_OVERLAY macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_OVERLAY))>
  endm

;GtkOverlay              typedef _GtkOverlay

gtk_overlay_get_type proto
gtk_overlay_new proto
gtk_overlay_add_overlay proto :ptr, :ptr
gtk_overlay_remove_overlay proto :ptr, :ptr
gtk_overlay_set_child proto :ptr, :ptr
gtk_overlay_get_child proto :ptr
gtk_overlay_get_measure_overlay proto :ptr, :ptr
gtk_overlay_set_measure_overlay proto :ptr, :ptr, :gboolean
gtk_overlay_get_clip_overlay proto :ptr, :ptr
gtk_overlay_set_clip_overlay proto :ptr, :ptr, :gboolean

endif

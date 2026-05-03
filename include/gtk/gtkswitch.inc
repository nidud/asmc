ifndef __GTK_SWITCH_H__
define __GTK_SWITCH_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_SWITCH <gtk_switch_get_type ()>
GTK_SWITCH macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SWITCH, GtkSwitch))>
  endm
GTK_IS_SWITCH macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SWITCH))>
  endm

gtk_switch_get_type proto
gtk_switch_new proto
gtk_switch_set_active proto :ptr, :gboolean
gtk_switch_get_active proto :ptr
gtk_switch_set_state proto :ptr, :gboolean
gtk_switch_get_state proto :ptr

endif

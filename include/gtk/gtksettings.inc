ifndef __GTK_SETTINGS_H__
define __GTK_SETTINGS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc

define GTK_TYPE_SETTINGS <gtk_settings_get_type>
GTK_SETTINGS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SETTINGS, GtkSettings))>
  endm
GTK_IS_SETTINGS macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SETTINGS))>
  endm

gtk_settings_get_type proto
gtk_settings_get_default proto
gtk_settings_get_for_display proto :ptr
gtk_settings_reset_property proto :ptr, :ptr

endif

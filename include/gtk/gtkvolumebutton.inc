ifndef __GTK_VOLUME_BUTTON_H__
define __GTK_VOLUME_BUTTON_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkscalebutton.inc

define GTK_TYPE_VOLUME_BUTTON <gtk_volume_button_get_type ()>
GTK_VOLUME_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_VOLUME_BUTTON, GtkVolumeButton))>
  endm
GTK_IS_VOLUME_BUTTON macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_VOLUME_BUTTON))>
  endm

_GtkVolumeButton        struct
parent                  GtkScaleButton <>
_GtkVolumeButton        ends
GtkVolumeButton         typedef _GtkVolumeButton

gtk_volume_button_get_type proto
gtk_volume_button_new proto

endif

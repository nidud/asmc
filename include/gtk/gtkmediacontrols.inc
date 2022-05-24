ifndef __GTK_MEDIA_CONTROLS_H__
define __GTK_MEDIA_CONTROLS_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmediastream.inc
include gtk/gtkwidget.inc

define GTK_TYPE_MEDIA_CONTROLS <gtk_media_controls_get_type ()>

gtk_media_controls_new proto :ptr

gtk_media_controls_get_media_stream proto :ptr
gtk_media_controls_set_media_stream proto :ptr, :ptr

endif

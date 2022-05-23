ifndef __GTK_VIDEO_H__
define __GTK_VIDEO_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkmediastream.inc
include gtk/gtkwidget.inc

define GTK_TYPE_VIDEO <gtk_video_get_type>

gtk_video_new proto
gtk_video_new_for_media_stream proto :ptr
gtk_video_new_for_file proto :ptr
gtk_video_new_for_filename proto :ptr
gtk_video_new_for_resource proto :ptr

gtk_video_get_media_stream proto :ptr
gtk_video_set_media_stream proto :ptr, :ptr
gtk_video_get_file proto :ptr
gtk_video_set_file proto :ptr, :ptr
gtk_video_set_filename proto :ptr, :ptr
gtk_video_set_resource proto :ptr, :ptr
gtk_video_get_autoplay proto :ptr
gtk_video_set_autoplay proto :ptr, :gboolean
gtk_video_get_loop proto :ptr
gtk_video_set_loop proto :ptr, :gboolean

endif

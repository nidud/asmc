ifndef __GTK_PICTURE_H__
define __GTK_PICTURE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_PICTURE <gtk_picture_get_type>

gtk_picture_new proto
gtk_picture_new_for_paintable proto :ptr
gtk_picture_new_for_pixbuf proto :ptr
gtk_picture_new_for_file proto :ptr
gtk_picture_new_for_filename proto :ptr
gtk_picture_new_for_resource proto :ptr

gtk_picture_set_paintable proto :ptr, :ptr
gtk_picture_get_paintable proto :ptr
gtk_picture_set_file proto :ptr, :ptr
gtk_picture_get_file proto :ptr
gtk_picture_set_filename proto :ptr, :ptr
gtk_picture_set_resource proto :ptr, :ptr
gtk_picture_set_pixbuf proto :ptr, :ptr

gtk_picture_set_keep_aspect_ratio proto :ptr, :gboolean
gtk_picture_get_keep_aspect_ratio proto :ptr
gtk_picture_set_can_shrink proto :ptr, :gboolean
gtk_picture_get_can_shrink proto :ptr

gtk_picture_set_alternative_text proto :ptr, :ptr
gtk_picture_get_alternative_text proto :ptr

endif

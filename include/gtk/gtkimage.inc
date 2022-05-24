ifndef __GTK_IMAGE_H__
define __GTK_IMAGE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gio/gio.inc
include gtk/gtkwidget.inc

define GTK_TYPE_IMAGE <gtk_image_get_type ()>
GTK_IMAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IMAGE, GtkImage))>
  endm
GTK_IS_IMAGE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IMAGE))>
  endm

;GtkImage                typedef _GtkImage


.enum GtkImageType {
  GTK_IMAGE_EMPTY,
  GTK_IMAGE_ICON_NAME,
  GTK_IMAGE_GICON,
  GTK_IMAGE_PAINTABLE
}

gtk_image_get_type proto

gtk_image_new proto
gtk_image_new_from_file proto :ptr
gtk_image_new_from_resource proto :ptr
gtk_image_new_from_pixbuf proto :ptr
gtk_image_new_from_paintable proto :ptr
gtk_image_new_from_icon_name proto :ptr
gtk_image_new_from_gicon proto :ptr

gtk_image_clear proto :ptr
gtk_image_set_from_file proto :ptr, :ptr
gtk_image_set_from_resource proto :ptr, :ptr
gtk_image_set_from_pixbuf proto :ptr, :ptr
gtk_image_set_from_paintable proto :ptr, :ptr
gtk_image_set_from_icon_name proto :ptr, :ptr
gtk_image_set_from_gicon proto :ptr, :ptr
gtk_image_set_pixel_size proto :ptr, :sdword
gtk_image_set_icon_size proto :ptr, :GtkIconSize

gtk_image_get_storage_type proto :ptr

gtk_image_get_paintable proto :ptr

gtk_image_get_icon_name proto :ptr
gtk_image_get_gicon proto :ptr
gtk_image_get_pixel_size proto :ptr
gtk_image_get_icon_size proto :ptr

endif

ifndef __GDK_TEXTURE_H__
define __GDK_TEXTURE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk-pixbuf/gdk-pixbuf.inc

define GDK_TYPE_TEXTURE <gdk_texture_get_type>

GDK_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_TEXTURE, GdkTexture))>
  endm
GDK_IS_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_TEXTURE))>
  endm

;GdkTextureClass         typedef _GdkTextureClass

define GDK_TEXTURE_ERROR       <gdk_texture_error_quark>

gdk_texture_error_quark proto

.enum GdkTextureError {
  GDK_TEXTURE_ERROR_TOO_LARGE,
  GDK_TEXTURE_ERROR_CORRUPT_IMAGE,
  GDK_TEXTURE_ERROR_UNSUPPORTED_CONTENT,
  GDK_TEXTURE_ERROR_UNSUPPORTED_FORMAT,
}

gdk_texture_get_type proto
gdk_texture_new_for_pixbuf proto :ptr
gdk_texture_new_from_resource proto :ptr
gdk_texture_new_from_file proto :ptr, :ptr
gdk_texture_new_from_filename proto :ptr, :ptr
gdk_texture_new_from_bytes proto :ptr, :ptr
gdk_texture_get_width proto :ptr
gdk_texture_get_height proto :ptr
gdk_texture_download proto :ptr, :ptr, :gsize
gdk_texture_save_to_png proto :ptr, :ptr
gdk_texture_save_to_png_bytes proto :ptr
gdk_texture_save_to_tiff proto :ptr, :ptr
gdk_texture_save_to_tiff_bytes proto :ptr

endif

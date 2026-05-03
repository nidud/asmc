ifndef GDK_PIXBUF_CORE_H
define GDK_PIXBUF_CORE_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib.inc
include glib-object.inc
include gio/gio.inc

include gdk-pixbuf/gdk-pixbuf-macros.inc

.enum GdkPixbufAlphaMode {
    GDK_PIXBUF_ALPHA_BILEVEL,
    GDK_PIXBUF_ALPHA_FULL
    }

.enum GdkColorspace {
    GDK_COLORSPACE_RGB
    }


define GDK_TYPE_PIXBUF <gdk_pixbuf_get_type ()>
GDK_PIXBUF macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_PIXBUF, GdkPixbuf))>
	endm
GDK_IS_PIXBUF macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_PIXBUF))>
	endm

CALLBACKC(GdkPixbufDestroyNotify, :ptr, :gpointer)

define GDK_PIXBUF_ERROR <gdk_pixbuf_error_quark ()>

.enum GdkPixbufError {
    GDK_PIXBUF_ERROR_CORRUPT_IMAGE,
    GDK_PIXBUF_ERROR_INSUFFICIENT_MEMORY,
    GDK_PIXBUF_ERROR_BAD_OPTION,
    GDK_PIXBUF_ERROR_UNKNOWN_TYPE,
    GDK_PIXBUF_ERROR_UNSUPPORTED_OPERATION,
    GDK_PIXBUF_ERROR_FAILED,
    GDK_PIXBUF_ERROR_INCOMPLETE_ANIMATION
    }

gdk_pixbuf_error_quark proto __cdecl
gdk_pixbuf_get_type proto __cdecl

ifndef GDK_PIXBUF_DISABLE_DEPRECATED
gdk_pixbuf_ref proto __cdecl :ptr
gdk_pixbuf_unref proto __cdecl :ptr
endif

gdk_pixbuf_get_colorspace proto __cdecl :ptr
gdk_pixbuf_get_n_channels proto __cdecl :ptr
gdk_pixbuf_get_has_alpha proto __cdecl :ptr
gdk_pixbuf_get_bits_per_sample proto __cdecl :ptr
gdk_pixbuf_get_pixels proto __cdecl :ptr
gdk_pixbuf_get_width proto __cdecl :ptr
gdk_pixbuf_get_height proto __cdecl :ptr
gdk_pixbuf_get_rowstride proto __cdecl :ptr
gdk_pixbuf_get_byte_length proto __cdecl :ptr
gdk_pixbuf_get_pixels_with_length proto __cdecl :ptr, :ptr
gdk_pixbuf_read_pixels proto __cdecl :ptr
gdk_pixbuf_read_pixel_bytes proto __cdecl :ptr
gdk_pixbuf_new proto __cdecl :GdkColorspace, :gboolean, :SINT, :SINT, :SINT
gdk_pixbuf_calculate_rowstride proto __cdecl :GdkColorspace, :gboolean, :SINT, :SINT, :SINT
gdk_pixbuf_copy proto __cdecl :ptr
gdk_pixbuf_new_subpixbuf proto __cdecl :ptr, :SINT, :SINT, :SINT, :SINT

ifdef G_OS_WIN32
gdk_pixbuf_new_from_file_utf8 proto __cdecl :ptr, :ptr
gdk_pixbuf_new_from_file_at_size_utf8 proto __cdecl :ptr, :SINT, :SINT, :ptr
gdk_pixbuf_new_from_file_at_scale_utf8 proto __cdecl :ptr, :SINT, :SINT, :gboolean, :ptr
endif

gdk_pixbuf_new_from_file proto __cdecl :ptr, :ptr
gdk_pixbuf_new_from_file_at_size proto __cdecl :ptr, :SINT, :SINT, :ptr
gdk_pixbuf_new_from_file_at_scale proto __cdecl :ptr, :SINT, :SINT, :gboolean, :ptr
gdk_pixbuf_new_from_resource proto __cdecl :ptr, :ptr
gdk_pixbuf_new_from_resource_at_scale proto __cdecl :ptr, :SINT, :SINT, :gboolean, :ptr
gdk_pixbuf_new_from_data proto __cdecl :ptr, :GdkColorspace, :gboolean, :SINT, :SINT, :SINT, :SINT, :GdkPixbufDestroyNotify, :gpointer
gdk_pixbuf_new_from_bytes proto __cdecl :ptr, :GdkColorspace, :gboolean, :SINT, :SINT, :SINT, :SINT
gdk_pixbuf_new_from_xpm_data proto __cdecl :ptr

ifndef GDK_PIXBUF_DISABLE_DEPRECATED
gdk_pixbuf_new_from_inline proto __cdecl :gint, :ptr, :gboolean, :ptr
endif

gdk_pixbuf_fill proto __cdecl :ptr, :guint32

ifndef __GTK_DOC_IGNORE__
ifdef G_OS_WIN32
define gdk_pixbuf_save <gdk_pixbuf_save_utf8>
endif
endif

gdk_pixbuf_save proto __Cdecl :ptr, :ptr, :ptr, :ptr, :vararg
gdk_pixbuf_savev proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
ifdef G_OS_WIN32
gdk_pixbuf_savev_utf8 proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
endif

CALLBACKC(GdkPixbufSaveFunc, :ptr, :gsize, :ptr, :gpointer)

gdk_pixbuf_save_to_callback proto __Cdecl :ptr, :GdkPixbufSaveFunc, :gpointer, :ptr, :ptr, :vararg
gdk_pixbuf_save_to_callbackv proto __cdecl :ptr, :GdkPixbufSaveFunc, :gpointer, :ptr, :ptr, :ptr, :ptr
gdk_pixbuf_save_to_buffer proto __Cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :vararg
gdk_pixbuf_save_to_bufferv proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gdk_pixbuf_new_from_stream proto __cdecl :ptr, :ptr, :ptr
gdk_pixbuf_new_from_stream_async proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
gdk_pixbuf_new_from_stream_finish proto __cdecl :ptr, :ptr
gdk_pixbuf_new_from_stream_at_scale proto __cdecl :ptr, :gint, :gint, :gboolean, :ptr, :ptr
gdk_pixbuf_new_from_stream_at_scale_async proto __cdecl :ptr, :gint, :gint, :gboolean, :ptr, :GAsyncReadyCallback, :gpointer
gdk_pixbuf_save_to_stream proto __Cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :vararg
gdk_pixbuf_save_to_stream_async proto __Cdecl :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer, :vararg
gdk_pixbuf_save_to_stream_finish proto __cdecl
gdk_pixbuf_save_to_streamv_async proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
gdk_pixbuf_save_to_streamv proto __cdecl :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gdk_pixbuf_add_alpha proto __cdecl :ptr, :gboolean, :guchar, :guchar, :guchar
gdk_pixbuf_copy_area proto __cdecl :ptr, :SINT, :SINT, :SINT, :SINT, :ptr, :SINT, :SINT
gdk_pixbuf_saturate_and_pixelate proto __cdecl :ptr, :ptr, :gfloat, :gboolean
gdk_pixbuf_apply_embedded_orientation proto __cdecl :ptr
gdk_pixbuf_set_option proto __cdecl :ptr, :ptr, :ptr
gdk_pixbuf_get_option proto __cdecl :ptr, :ptr
gdk_pixbuf_remove_option proto __cdecl
gdk_pixbuf_get_options proto __cdecl :ptr
gdk_pixbuf_copy_options proto __cdecl :ptr, :ptr

endif

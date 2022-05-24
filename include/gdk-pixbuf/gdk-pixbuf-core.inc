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

CALLBACKC(GdkPixbufDestroyNotify, :ptr guchar, :gpointer)

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

gdk_pixbuf_ref proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_unref proto __cdecl \
		pixbuf: ptr GdkPixbuf

endif

gdk_pixbuf_get_colorspace proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_n_channels proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_has_alpha proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_bits_per_sample proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_pixels proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_width proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_height proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_rowstride proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_byte_length proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_get_pixels_with_length proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		length: ptr guint

gdk_pixbuf_read_pixels proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_read_pixel_bytes proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_new proto __cdecl \
	    colorspace: GdkColorspace,
	     has_alpha: gboolean,
       bits_per_sample: SINT,
		 width: SINT,
		height: SINT

gdk_pixbuf_calculate_rowstride proto __cdecl \
	    colorspace: GdkColorspace,
	     has_alpha: gboolean,
       bits_per_sample: SINT,
		 width: SINT,
		height: SINT


gdk_pixbuf_copy proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_new_subpixbuf proto __cdecl \
	    src_pixbuf: ptr GdkPixbuf,
		 src_x: SINT,
		 src_y: SINT,
		 width: SINT,
		height: SINT

ifdef G_OS_WIN32

gdk_pixbuf_new_from_file_utf8 proto __cdecl \
	      filename: ptr char_t,
		 error: ptr GError

gdk_pixbuf_new_from_file_at_size_utf8 proto __cdecl \
	      filename: ptr char_t,
		 width: SINT,
		height: SINT,
		 error: ptr GError

gdk_pixbuf_new_from_file_at_scale_utf8 proto __cdecl \
	      filename: ptr char_t,
		 width: SINT,
		height: SINT,
 preserve_aspect_ratio: gboolean,
		 error: ptr GError

endif

gdk_pixbuf_new_from_file proto __cdecl \
	      filename: ptr char_t,
		 error: ptr GError

gdk_pixbuf_new_from_file_at_size proto __cdecl \
	      filename: ptr char_t,
		 width: SINT,
		height: SINT,
		 error: ptr GError

gdk_pixbuf_new_from_file_at_scale proto __cdecl \
	      filename: ptr char_t,
		 width: SINT,
		height: SINT,
 preserve_aspect_ratio: gboolean,
		 error: ptr GError

gdk_pixbuf_new_from_resource proto __cdecl \
	 resource_path: ptr char_t,
		 error: ptr GError

gdk_pixbuf_new_from_resource_at_scale proto __cdecl \
	 resource_path: ptr char_t,
		 width: SINT,
		height: SINT,
 preserve_aspect_ratio: gboolean,
		 error: ptr GError

gdk_pixbuf_new_from_data proto __cdecl \
		  data: ptr guchar,
	    colorspace: GdkColorspace,
	     has_alpha: gboolean,
       bits_per_sample: SINT,
		 width: SINT,
		height: SINT,
	     rowstride: SINT,
	    destroy_fn: GdkPixbufDestroyNotify,
       destroy_fn_data: gpointer

gdk_pixbuf_new_from_bytes proto __cdecl \
		  data: ptr GBytes,
	    colorspace: GdkColorspace,
	     has_alpha: gboolean,
       bits_per_sample: SINT,
		 width: SINT,
		height: SINT,
	     rowstride: SINT


gdk_pixbuf_new_from_xpm_data proto __cdecl \
		  data: ptr char_t

ifndef GDK_PIXBUF_DISABLE_DEPRECATED

gdk_pixbuf_new_from_inline proto __cdecl \
	   data_length: gint,
		  data: ptr guint8,
	   copy_pixels: gboolean,
		 error: ptr GError

endif

gdk_pixbuf_fill proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		 pixel: guint32

ifndef __GTK_DOC_IGNORE__
ifdef G_OS_WIN32
define gdk_pixbuf_save <gdk_pixbuf_save_utf8>
endif
endif

gdk_pixbuf_save proto _CDecl \
		pixbuf: ptr GdkPixbuf,
	      filename: ptr char_t,
		  type: ptr char_t,
		 error: ptr GError,
		      : vararg

gdk_pixbuf_savev proto __cdecl \
		pixbuf: ptr GdkPixbuf,
	      filename: ptr char_t,
		  type: ptr char_t,
	   option_keys: ptr char_t,
	 option_values: ptr char_t,
		 error: ptr GError


ifdef G_OS_WIN32

gdk_pixbuf_savev_utf8 proto __cdecl \
		pixbuf: ptr GdkPixbuf,
	      filename: ptr char_t,
		  type: ptr char_t,
	   option_keys: ptr char_t,
	 option_values: ptr char_t,
		 error: ptr GError

endif


CALLBACKC(GdkPixbufSaveFunc, :ptr gchar, :gsize, :ptr ptr GError, :gpointer)

gdk_pixbuf_save_to_callback proto _CDecl \
		pixbuf: ptr GdkPixbuf,
	     save_func: GdkPixbufSaveFunc,
	     user_data: gpointer,
		  type: ptr char_t,
		 error: ptr GError,
		      : vararg

gdk_pixbuf_save_to_callbackv proto __cdecl \
		pixbuf: ptr GdkPixbuf,
	     save_func: GdkPixbufSaveFunc,
	     user_data: gpointer,
		  type: ptr char_t,
	   option_keys: ptr char_t,
	 option_values: ptr char_t,
		 error: ptr GError

gdk_pixbuf_save_to_buffer proto _CDecl \
		pixbuf: ptr GdkPixbuf,
		buffer: ptr gchar,
	   buffer_size: ptr gsize,
		  type: ptr char_t,
		 error: ptr GError,
		      : vararg

gdk_pixbuf_save_to_bufferv proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		buffer: ptr gchar,
	   buffer_size: ptr gsize,
		  type: ptr char_t,
	   option_keys: ptr char_t,
	 option_values: ptr char_t,
		 error: ptr GError

gdk_pixbuf_new_from_stream proto __cdecl \
		stream: ptr GInputStream,
	   cancellable: ptr GCancellable,
		 error: ptr GError

gdk_pixbuf_new_from_stream_async proto __cdecl \
		stream: ptr GInputStream,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

gdk_pixbuf_new_from_stream_finish proto __cdecl \
	  async_result: ptr GAsyncResult,
		 error: ptr GError

gdk_pixbuf_new_from_stream_at_scale proto __cdecl \
		stream: ptr GInputStream,
		 width: gint,
		height: gint,
 preserve_aspect_ratio: gboolean,
	   cancellable: ptr GCancellable,
		 error: ptr GError

gdk_pixbuf_new_from_stream_at_scale_async proto __cdecl \
		stream: ptr GInputStream,
		 width: gint,
		height: gint,
 preserve_aspect_ratio: gboolean,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

gdk_pixbuf_save_to_stream proto _CDecl \
		pixbuf: ptr GdkPixbuf,
		stream: ptr GOutputStream,
		  type: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError,
		      : vararg

gdk_pixbuf_save_to_stream_async proto _CDecl \
		pixbuf: ptr GdkPixbuf,
		stream: ptr GOutputStream,
		  type: ptr gchar,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer,
		      : vararg

gdk_pixbuf_save_to_stream_finish proto __cdecl

gdk_pixbuf_save_to_streamv_async proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		stream: ptr GOutputStream,
		  type: ptr gchar,
	   option_keys: ptr gchar,
	 option_values: ptr gchar,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

gdk_pixbuf_save_to_streamv proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		stream: ptr GOutputStream,
		  type: ptr char_t,
	   option_keys: ptr char_t,
	 option_values: ptr char_t,
	   cancellable: ptr GCancellable,
		 error: ptr GError

gdk_pixbuf_add_alpha proto __cdecl \
		pixbuf: ptr GdkPixbuf,
      substitute_color: gboolean,
		     r: guchar,
		     g: guchar,
		     b: guchar

gdk_pixbuf_copy_area proto __cdecl \
	    src_pixbuf: ptr GdkPixbuf,
		 src_x: SINT,
		 src_y: SINT,
		 width: SINT,
		height: SINT,
	   dest_pixbuf: ptr GdkPixbuf,
		dest_x: SINT,
		dest_y: SINT

gdk_pixbuf_saturate_and_pixelate proto __cdecl \
		   src: ptr GdkPixbuf,
		  dest: ptr GdkPixbuf,
	    saturation: gfloat,
	      pixelate: gboolean


gdk_pixbuf_apply_embedded_orientation proto __cdecl \
		   src: ptr GdkPixbuf


gdk_pixbuf_set_option proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		   key: ptr gchar,
		 value: ptr gchar


gdk_pixbuf_get_option proto __cdecl \
		pixbuf: ptr GdkPixbuf,
		   key: ptr gchar


gdk_pixbuf_remove_option proto __cdecl

gdk_pixbuf_get_options proto __cdecl \
		pixbuf: ptr GdkPixbuf

gdk_pixbuf_copy_options proto __cdecl \
	    src_pixbuf: ptr GdkPixbuf,
	   dest_pixbuf: ptr GdkPixbuf


endif

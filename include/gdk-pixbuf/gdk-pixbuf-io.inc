ifndef GDK_PIXBUF_IO_H
define GDK_PIXBUF_IO_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include stdio.inc
include glib.inc
;include gmodule.inc
include gdk-pixbuf/gdk-pixbuf-core.inc
include gdk-pixbuf/gdk-pixbuf-animation.inc

gdk_pixbuf_init_modules proto __cdecl \
		  path: ptr char_t,
		 error: ptr ptr GError


gdk_pixbuf_format_get_type proto __cdecl
gdk_pixbuf_get_formats proto __cdecl

gdk_pixbuf_format_get_name proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_get_description proto __cdecl

gdk_pixbuf_format_get_mime_types proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_get_extensions proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_is_save_option_supported proto __cdecl
gdk_pixbuf_format_is_writable proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_is_scalable proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_is_disabled proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_set_disabled proto __cdecl \
		format: ptr GdkPixbufFormat,
	      disabled: gboolean

gdk_pixbuf_format_get_license proto __cdecl \
		format: ptr GdkPixbufFormat

gdk_pixbuf_get_file_info proto __cdecl \
		 gchar: ptr filename,
		 width: ptr gint,
		height: ptr gint

gdk_pixbuf_get_file_info_async proto __cdecl \
	      filename: ptr gchar,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

gdk_pixbuf_get_file_info_finish proto __cdecl \
	  GAsyncResult: ptr async_result,
		 width: ptr gint,
		height: ptr gint,
		 error: ptr GError

gdk_pixbuf_format_copy proto __cdecl\
		format: ptr GdkPixbufFormat

gdk_pixbuf_format_free proto __cdecl \
		format: ptr GdkPixbufFormat


ifdef GDK_PIXBUF_ENABLE_BACKEND

CALLBACKC(GdkPixbufModuleSizeFunc, :ptr gint, :ptr gint, :gpointer)
CALLBACKC(GdkPixbufModulePreparedFunc, :ptr GdkPixbuf, :ptr GdkPixbufAnimation, :gpointer)
CALLBACKC(GdkPixbufModuleUpdatedFunc, :ptr GdkPixbuf, :int_t, :int_t, :int_t, :int_t, :gpointer)

GdkPixbufModulePattern	STRUC
prefix			ptr char_t ?
mask			ptr char_t ?
relevance		SINT ?
GdkPixbufModulePattern	ENDS

CALLBACKC(GdkPixbufModuleLoadFunc, :ptr FILE, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleLoadXpmDataFunc, :ptr)
CALLBACKC(GdkPixbufModuleLoadAnimationFunc, :ptr FILE, :ptr)
CALLBACKC(GdkPixbufModuleBeginLoadFunc, :GdkPixbufModuleSizeFunc, :GdkPixbufModulePreparedFunc, :GdkPixbufModuleUpdatedFunc, :gpointer, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleStopLoadFunc, :gpointer, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleIncrementLoadFunc, :gpointer, :ptr guchar, :guint, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleSaveFunc, :ptr FILE, :ptr GdkPixbuf, :ptr ptr gchar, :ptr ptr gchar, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleSaveCallbackFunc, :GdkPixbufSaveFunc, :gpointer, :ptr GdkPixbuf, :ptr ptr gchar, :ptr ptr gchar, :ptr ptr GError)
CALLBACKC(GdkPixbufModuleSaveOptionSupportedFunc, :ptr gchar)

GdkPixbufModule		STRUC
module_name		ptr char_t ?
module_path		ptr char_t ?
module			ptr GModule ?
info			ptr GdkPixbufFormat ?
load			GdkPixbufModuleLoadFunc ?
load_xpm_data		GdkPixbufModuleLoadXpmDataFunc ?
begin_load		GdkPixbufModuleBeginLoadFunc ?
stop_load		GdkPixbufModuleStopLoadFunc ?
load_increment		GdkPixbufModuleIncrementLoadFunc ?
load_animation		GdkPixbufModuleLoadAnimationFunc ?
save			GdkPixbufModuleSaveFunc ?
save_to_callback	GdkPixbufModuleSaveCallbackFunc ?
is_save_option_supported GdkPixbufModuleSaveOptionSupportedFunc ?
_reserved1		proc
_reserved2		proc
_reserved3		proc
_reserved4		proc
GdkPixbufModule		ENDS

CALLBACKC(GdkPixbufModuleFillVtableFunc, :ptr GdkPixbufModule)
CALLBACKC(GdkPixbufModuleFillInfoFunc, :ptr GdkPixbufFormat)

.enum GdkPixbufFormatFlags {
    GDK_PIXBUF_FORMAT_WRITABLE = 1 shl 0,
    GDK_PIXBUF_FORMAT_SCALABLE = 1 shl 1,
    GDK_PIXBUF_FORMAT_THREADSAFE = 1 shl 2
    }

GdkPixbufFormat		STRUC
name			ptr gchar ?
signature		ptr GdkPixbufModulePattern ?
domain			ptr gchar ?
description		ptr gchar ?
mime_types		ptr gchar ?
extensions		ptr gchar ?
flags			guint32 ?
disabled		gboolean ?
license			ptr gchar ?
GdkPixbufFormat		ENDS

endif

endif

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

gdk_pixbuf_init_modules proto __cdecl :ptr, :ptr
gdk_pixbuf_format_get_type proto __cdecl
gdk_pixbuf_get_formats proto __cdecl
gdk_pixbuf_format_get_name proto __cdecl :ptr
gdk_pixbuf_format_get_description proto __cdecl
gdk_pixbuf_format_get_mime_types proto __cdecl :ptr
gdk_pixbuf_format_get_extensions proto __cdecl :ptr
gdk_pixbuf_format_is_save_option_supported proto __cdecl
gdk_pixbuf_format_is_writable proto __cdecl :ptr
gdk_pixbuf_format_is_scalable proto __cdecl :ptr
gdk_pixbuf_format_is_disabled proto __cdecl :ptr
gdk_pixbuf_format_set_disabled proto __cdecl :ptr, :gboolean
gdk_pixbuf_format_get_license proto __cdecl :ptr
gdk_pixbuf_get_file_info proto __cdecl :ptr, :ptr, :ptr
gdk_pixbuf_get_file_info_async proto __cdecl :ptr, :ptr, :GAsyncReadyCallback, :gpointer
gdk_pixbuf_get_file_info_finish proto __cdecl :ptr, :ptr, :ptr, :ptr
gdk_pixbuf_format_copy proto __cdecl :ptr
gdk_pixbuf_format_free proto __cdecl :ptr

ifdef GDK_PIXBUF_ENABLE_BACKEND

CALLBACKC(GdkPixbufModuleSizeFunc, :ptr, :ptr, :gpointer)
CALLBACKC(GdkPixbufModulePreparedFunc, :ptr, :ptr, :gpointer)
CALLBACKC(GdkPixbufModuleUpdatedFunc, :ptr, :int_t, :int_t, :int_t, :int_t, :gpointer)

GdkPixbufModulePattern	STRUC
prefix			ptr_t ?
mask			ptr_t ?
relevance		SINT ?
GdkPixbufModulePattern	ENDS

CALLBACKC(GdkPixbufModuleLoadFunc, :ptr, :ptr)
CALLBACKC(GdkPixbufModuleLoadXpmDataFunc, :ptr)
CALLBACKC(GdkPixbufModuleLoadAnimationFunc, :ptr, :ptr)
CALLBACKC(GdkPixbufModuleBeginLoadFunc, :GdkPixbufModuleSizeFunc, :GdkPixbufModulePreparedFunc, :GdkPixbufModuleUpdatedFunc, :gpointer, :ptr)
CALLBACKC(GdkPixbufModuleStopLoadFunc, :gpointer, :ptr)
CALLBACKC(GdkPixbufModuleIncrementLoadFunc, :gpointer, :ptr, :guint, :ptr)
CALLBACKC(GdkPixbufModuleSaveFunc, :ptr, :ptr, :ptr, :ptr, :ptr)
CALLBACKC(GdkPixbufModuleSaveCallbackFunc, :GdkPixbufSaveFunc, :gpointer, :ptr, :ptr, :ptr, :ptr)
CALLBACKC(GdkPixbufModuleSaveOptionSupportedFunc, :ptr)

GdkPixbufModule		STRUC
module_name		ptr_t ?
module_path		ptr_t ?
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

CALLBACKC(GdkPixbufModuleFillVtableFunc, :ptr)
CALLBACKC(GdkPixbufModuleFillInfoFunc, :ptr)

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

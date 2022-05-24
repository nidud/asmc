ifndef GDK_PIXBUF_ANIMATION_H
define GDK_PIXBUF_ANIMATION_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

include glib-object.inc
include gdk-pixbuf/gdk-pixbuf-core.inc

define GDK_TYPE_PIXBUF_ANIMATION <gdk_pixbuf_animation_get_type ()>
GDK_PIXBUF_ANIMATION macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_PIXBUF_ANIMATION, GdkPixbufAnimation))>
	endm
GDK_IS_PIXBUF_ANIMATION macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_PIXBUF_ANIMATION))>
	endm

define GDK_TYPE_PIXBUF_ANIMATION_ITER equ <gdk_pixbuf_animation_iter_get_type ()>
GDK_PIXBUF_ANIMATION_ITER macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_PIXBUF_ANIMATION_ITER, GdkPixbufAnimationIter))>
	endm
GDK_IS_PIXBUF_ANIMATION_ITER macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_PIXBUF_ANIMATION_ITER))>
	endm

gdk_pixbuf_animation_get_type proto __cdecl

ifdef G_OS_WIN32

gdk_pixbuf_animation_new_from_file_utf8 proto __cdecl \
	      filename: ptr char_t,
		 error: ptr GError

endif

gdk_pixbuf_animation_new_from_file proto __cdecl \
	      filename: ptr char_t,
		 error: ptr GError

gdk_pixbuf_animation_new_from_stream proto __cdecl \
		stream: ptr GInputStream,
	   cancellable: ptr GCancellable,
		 error: ptr GError

gdk_pixbuf_animation_new_from_stream_async proto __cdecl \
		stream: ptr GInputStream,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

gdk_pixbuf_animation_new_from_stream_finish proto __cdecl \
	  async_result: ptr GAsyncResult,
		 error: ptr GError

gdk_pixbuf_animation_new_from_resource proto __cdecl \
	 resource_path: ptr char_t,
		 error: ptr GError


ifndef GDK_PIXBUF_DISABLE_DEPRECATED

gdk_pixbuf_animation_ref proto __cdecl \
	     animation: ptr GdkPixbufAnimation

gdk_pixbuf_animation_unref proto __cdecl \
	     animation: ptr GdkPixbufAnimation

endif

gdk_pixbuf_animation_get_width proto __cdecl \
	     animation: ptr GdkPixbufAnimation

gdk_pixbuf_animation_get_height proto __cdecl \
	     animation: ptr GdkPixbufAnimation

gdk_pixbuf_animation_is_static_image proto __cdecl \
	     animation: ptr GdkPixbufAnimation

gdk_pixbuf_animation_get_static_image proto __cdecl \
	     animation: ptr GdkPixbufAnimation


gdk_pixbuf_animation_get_iter proto __cdecl \
	     animation: ptr GdkPixbufAnimation,
	    start_time: ptr GTimeVal

gdk_pixbuf_animation_iter_get_type proto __cdecl

gdk_pixbuf_animation_iter_get_delay_time proto __cdecl \
		  iter: ptr GdkPixbufAnimationIter

gdk_pixbuf_animation_iter_get_pixbuf proto __cdecl \
		  iter: ptr GdkPixbufAnimationIter

gdk_pixbuf_animation_iter_on_currently_loading_frame proto __cdecl \
		  iter: ptr GdkPixbufAnimationIter


gdk_pixbuf_animation_iter_advance proto __cdecl \
		  iter: ptr GdkPixbufAnimationIter,
	  current_time: ptr GTimeVal

ifdef GDK_PIXBUF_ENABLE_BACKEND



GDK_PIXBUF_ANIMATION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_PIXBUF_ANIMATION, GdkPixbufAnimationClass))>
	endm
GDK_IS_PIXBUF_ANIMATION_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_PIXBUF_ANIMATION))>
	endm
GDK_PIXBUF_ANIMATION_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_PIXBUF_ANIMATION, GdkPixbufAnimationClass))>
	endm


GdkPixbufAnimation	STRUC
parent_instance		GObject <>
GdkPixbufAnimation	ENDS

GdkPixbufAnimationClass	 STRUC
parent_class		GObjectClass <>
is_static_image		proc :ptr GdkPixbufAnimation
get_static_image	proc :ptr GdkPixbufAnimation
get_size		proc :ptr GdkPixbufAnimation, :ptr int_t, :ptr int_t
get_iter		proc :ptr GdkPixbufAnimation, :ptr GTimeVal
GdkPixbufAnimationClass ENDS

GDK_PIXBUF_ANIMATION_ITER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_PIXBUF_ANIMATION_ITER, GdkPixbufAnimationIterClass))>
	endm
GDK_IS_PIXBUF_ANIMATION_ITER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_PIXBUF_ANIMATION_ITER))>
	endm
GDK_PIXBUF_ANIMATION_ITER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_PIXBUF_ANIMATION_ITER, GdkPixbufAnimationIterClass))>
	endm

GdkPixbufAnimationIter	STRUC
parent_instance		GObject <>
GdkPixbufAnimationIter	ENDS

GdkPixbufAnimationIterClass STRUC
parent_class		GObjectClass <>
get_delay_time		proc :ptr GdkPixbufAnimationIter
get_pixbuf		proc :ptr GdkPixbufAnimationIter
on_currently_loading_frame proc :ptr GdkPixbufAnimationIter
advance			proc :ptr GdkPixbufAnimationIter, :ptr GTimeVal
GdkPixbufAnimationIterClass ENDS

gdk_pixbuf_non_anim_get_type proto __cdecl

gdk_pixbuf_non_anim_new proto __cdecl \
		pixbuf: ptr GdkPixbuf

endif

endif

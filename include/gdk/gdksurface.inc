ifndef __GDK_SURFACE_H__
define __GDK_SURFACE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc
include gdk/gdkevents.inc
include gdk/gdkframeclock.inc
include gdk/gdkmonitor.inc
include gdk/gdkpopuplayout.inc

;GdkSurfaceClass         typedef _GdkSurfaceClass

define GDK_TYPE_SURFACE <gdk_surface_get_type ()>
GDK_SURFACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_SURFACE, GdkSurface))>
  endm
GDK_SURFACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_SURFACE, GdkSurfaceClass))>
  endm
GDK_IS_SURFACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_SURFACE))>
  endm
GDK_IS_SURFACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_SURFACE))>
  endm
GDK_SURFACE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_SURFACE, GdkSurfaceClass))>
  endm

gdk_surface_get_type proto
gdk_surface_new_toplevel proto :ptr
gdk_surface_new_popup proto :ptr, :gboolean
gdk_surface_destroy proto :ptr
gdk_surface_is_destroyed proto :ptr
gdk_surface_get_display proto :ptr
gdk_surface_hide proto :ptr
gdk_surface_set_input_region proto :ptr, :ptr
gdk_surface_get_mapped proto :ptr
gdk_surface_set_cursor proto :ptr, :ptr
gdk_surface_get_cursor proto :ptr
gdk_surface_set_device_cursor proto :ptr, :ptr, :ptr
gdk_surface_get_device_cursor proto :ptr, :ptr
gdk_surface_get_width proto :ptr
gdk_surface_get_height proto :ptr
gdk_surface_translate_coordinates proto :ptr, :ptr, :ptr, :ptr
gdk_surface_get_scale_factor proto :ptr
gdk_surface_get_device_position proto :ptr, :ptr, :ptr, :ptr, :ptr
gdk_surface_create_similar_surface proto :ptr, :cairo_content_t, :gint, :gint
gdk_surface_beep proto :ptr
gdk_surface_queue_render proto :ptr
gdk_surface_request_layout proto :ptr
gdk_surface_get_frame_clock proto :ptr
gdk_surface_set_opaque_region proto :ptr, :ptr
gdk_surface_create_cairo_context proto :ptr
gdk_surface_create_gl_context proto :ptr, :ptr

endif

ifndef __GDK_FRAME_TIMINGS_H__
__GDK_FRAME_TIMINGS_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdkversionmacros.inc

;GType
gdk_frame_timings_get_type proto __cdecl

;GdkFrameTimings
gdk_frame_timings_ref proto __cdecl \
               timings: ptr GdkFrameTimings

;void
gdk_frame_timings_unref proto __cdecl \
               timings: ptr GdkFrameTimings


;gint64
gdk_frame_timings_get_frame_counter proto __cdecl \
               timings: ptr GdkFrameTimings

;gboolean
gdk_frame_timings_get_complete proto __cdecl \
               timings: ptr GdkFrameTimings

;gint64
gdk_frame_timings_get_frame_time proto __cdecl \
               timings: ptr GdkFrameTimings

;gint64
gdk_frame_timings_get_presentation_time proto __cdecl \
               timings: ptr GdkFrameTimings

;gint64
gdk_frame_timings_get_refresh_interval proto __cdecl \
               timings: ptr GdkFrameTimings


;gint64
gdk_frame_timings_get_predicted_presentation_time proto __cdecl \
               timings: ptr GdkFrameTimings


endif

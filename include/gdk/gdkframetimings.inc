ifndef __GDK_FRAME_TIMINGS_H__
define __GDK_FRAME_TIMINGS_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdkversionmacros.inc

;GdkFrameTimings         typedef _GdkFrameTimings

gdk_frame_timings_get_type proto
gdk_frame_timings_ref proto :ptr
gdk_frame_timings_unref proto :ptr
gdk_frame_timings_get_frame_counter proto :ptr
gdk_frame_timings_get_complete proto :ptr
gdk_frame_timings_get_frame_time proto :ptr
gdk_frame_timings_get_presentation_time proto :ptr
gdk_frame_timings_get_refresh_interval proto :ptr
gdk_frame_timings_get_predicted_presentation_time proto :ptr

endif

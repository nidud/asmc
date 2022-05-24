ifndef __GDK_FRAME_CLOCK_H__
define __GDK_FRAME_CLOCK_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkframetimings.inc

define GDK_TYPE_FRAME_CLOCK <gdk_frame_clock_get_type ()>
GDK_FRAME_CLOCK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_FRAME_CLOCK, GdkFrameClock))>
  endm
GDK_FRAME_CLOCK_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_FRAME_CLOCK, GdkFrameClockClass))>
  endm
GDK_IS_FRAME_CLOCK macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_FRAME_CLOCK))>
  endm
GDK_IS_FRAME_CLOCK_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_FRAME_CLOCK))>
  endm
GDK_FRAME_CLOCK_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_FRAME_CLOCK, GdkFrameClockClass))>
  endm

;GdkFrameClock           typedef _GdkFrameClock
;GdkFrameClockPrivate    typedef _GdkFrameClockPrivate
;GdkFrameClockClass      typedef _GdkFrameClockClass

.enum GdkFrameClockPhase {
  GDK_FRAME_CLOCK_PHASE_NONE          = 0,
  GDK_FRAME_CLOCK_PHASE_FLUSH_EVENTS  = 1 shl 0,
  GDK_FRAME_CLOCK_PHASE_BEFORE_PAINT  = 1 shl 1,
  GDK_FRAME_CLOCK_PHASE_UPDATE        = 1 shl 2,
  GDK_FRAME_CLOCK_PHASE_LAYOUT        = 1 shl 3,
  GDK_FRAME_CLOCK_PHASE_PAINT         = 1 shl 4,
  GDK_FRAME_CLOCK_PHASE_RESUME_EVENTS = 1 shl 5,
  GDK_FRAME_CLOCK_PHASE_AFTER_PAINT   = 1 shl 6
}

gdk_frame_clock_get_type proto
gdk_frame_clock_get_frame_time proto :ptr
gdk_frame_clock_request_phase proto :ptr, :GdkFrameClockPhase
gdk_frame_clock_begin_updating proto :ptr
gdk_frame_clock_end_updating proto :ptr
gdk_frame_clock_get_frame_counter proto :ptr
gdk_frame_clock_get_history_start proto :ptr
gdk_frame_clock_get_timings proto :ptr, :gint64
gdk_frame_clock_get_current_timings proto :ptr
gdk_frame_clock_get_refresh_info proto :ptr, :gint64, :ptr, :ptr
gdk_frame_clock_get_fps proto :ptr

endif

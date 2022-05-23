ifndef __GSK_RENDERER_H__
define __GSK_RENDERER_H__

if not defined (__GSK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gsk/gsk.h can be included directly.">
endif

include gsk/gsktypes.inc
include gsk/gskrendernode.inc

define GSK_TYPE_RENDERER <gsk_renderer_get_type>

GSK_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_RENDERER, GskRenderer))>
  endm
GSK_IS_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_RENDERER))>
  endm

;GskRendererClass        typedef _GskRendererClass

gsk_renderer_get_type proto
gsk_renderer_new_for_surface proto :ptr
gsk_renderer_get_surface proto :ptr
gsk_renderer_realize proto :ptr, :ptr, :ptr
gsk_renderer_unrealize proto :ptr
gsk_renderer_is_realized proto :ptr
gsk_renderer_render_texture proto :ptr, :ptr, :ptr
gsk_renderer_render proto :ptr, :ptr, :ptr

endif

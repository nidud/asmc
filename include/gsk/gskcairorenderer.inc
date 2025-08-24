ifndef __GSK_CAIRO_RENDERER_H__
define __GSK_CAIRO_RENDERER_H__

include cairo.inc
include gsk/gskrenderer.inc

define GSK_TYPE_CAIRO_RENDERER <gsk_cairo_renderer_get_type ()>

GSK_CAIRO_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_CAIRO_RENDERER, GskCairoRenderer))>
  endm
GSK_IS_CAIRO_RENDERER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_CAIRO_RENDERER))>
  endm
GSK_CAIRO_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GSK_TYPE_CAIRO_RENDERER, GskCairoRendererClass))>
  endm
GSK_IS_CAIRO_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GSK_TYPE_CAIRO_RENDERER))>
  endm
GSK_CAIRO_RENDERER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GSK_TYPE_CAIRO_RENDERER, GskCairoRendererClass))>
  endm

gsk_cairo_renderer_get_type proto
gsk_cairo_renderer_new proto

endif

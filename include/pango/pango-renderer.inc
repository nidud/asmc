ifndef __PANGO_RENDERER_H_
define __PANGO_RENDERER_H_

include pango/pango-layout.inc

define PANGO_TYPE_RENDERER <pango_renderer_get_type ()>
PANGO_RENDERER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_RENDERER, PangoRenderer))>
  endm
PANGO_IS_RENDERER macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_RENDERER))>
  endm
PANGO_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_RENDERER, PangoRendererClass))>
  endm
PANGO_IS_RENDERER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_RENDERER))>
  endm
PANGO_RENDERER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_RENDERER, PangoRendererClass))>
  endm

.enum PangoRenderPart {
  PANGO_RENDER_PART_FOREGROUND,
  PANGO_RENDER_PART_BACKGROUND,
  PANGO_RENDER_PART_UNDERLINE,
  PANGO_RENDER_PART_STRIKETHROUGH,
  PANGO_RENDER_PART_OVERLINE
  }

PangoRenderer           struct
parent_instance         GObject <>
underline               PangoUnderline ?
strikethrough           gboolean ?
active_count            sdword ?
matrix                  ptr PangoMatrix ?
priv                    ptr PangoRendererPrivate ?
PangoRenderer           ends

PangoRendererClass      struct
parent_class            GObjectClass <>
draw_glyphs             proc :ptr, :ptr, :ptr, :sdword, :sdword
draw_rectangle          proc :ptr, :PangoRenderPart, :sdword, :sdword, :sdword, :sdword
draw_error_underline    proc :ptr, :sdword, :sdword, :sdword, :sdword
draw_shape              proc :ptr, :ptr, :sdword, :sdword
draw_trapezoid          proc :ptr, :PangoRenderPart, :real8, :real8, :real8, :real8, :real8, :real8
draw_glyph              proc :ptr, :ptr, :PangoGlyph, :real8, :real8
part_changed            proc :ptr, :PangoRenderPart
begin                   proc :ptr
_end                    proc :ptr
prepare_run             proc :ptr, :ptr
draw_glyph_item         proc :ptr, :ptr, :ptr, :sdword, :sdword
_pango_reserved2        proc
_pango_reserved3        proc
_pango_reserved4        proc
PangoRendererClass      ends

pango_renderer_get_type proto

pango_renderer_draw_layout proto :ptr, :ptr, :sdword, :sdword
pango_renderer_draw_layout_line proto :ptr, :ptr, :sdword, :sdword
pango_renderer_draw_glyphs proto :ptr, :ptr, :ptr, :sdword, :sdword
pango_renderer_draw_glyph_item proto :ptr, :ptr, :ptr, :sdword, :sdword
pango_renderer_draw_rectangle proto :ptr, :PangoRenderPart, :sdword, :sdword, :sdword, :sdword
pango_renderer_draw_error_underline proto :ptr, :sdword, :sdword, :sdword, :sdword
pango_renderer_draw_trapezoid proto :ptr, :PangoRenderPart, :real8, :real8, :real8, :real8, :real8, :real8
pango_renderer_draw_glyph proto :ptr, :ptr, :PangoGlyph, :real8, :real8

pango_renderer_activate proto :ptr
pango_renderer_deactivate proto :ptr
pango_renderer_part_changed proto :ptr, :PangoRenderPart
pango_renderer_set_color proto :ptr, :PangoRenderPart, :ptr
pango_renderer_get_color proto :ptr, :PangoRenderPart
pango_renderer_set_alpha proto :ptr, :PangoRenderPart, :guint16
pango_renderer_get_alpha proto :ptr, :PangoRenderPart
pango_renderer_set_matrix proto :ptr, :ptr
pango_renderer_get_matrix proto :ptr
pango_renderer_get_layout proto :ptr
pango_renderer_get_layout_line proto :ptr

endif


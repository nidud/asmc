ifndef __GSK_RENDER_NODE_H__
define __GSK_RENDER_NODE_H__

if not defined (__GSK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gsk/gsk.h can be included directly.">
endif

include gsk/gskroundedrect.inc
include gsk/gsktypes.inc
include gsk/gskglshader.inc
include gtk/css/gtkcss.inc

define GSK_TYPE_RENDER_NODE (gsk_render_node_get_type ())

GSK_IS_RENDER_NODE macro obj
  exitm<((obj) != NULL)>
  endm

define GSK_SERIALIZATION_ERROR <gsk_serialization_error_quark>

;GskRenderNode           typedef _GskRenderNode

_GskColorStop           STRUC
offs                    real4 ?
color                   GdkRGBA <>
_GskColorStop           ENDS
GskColorStop            typedef _GskColorStop

_GskShadow              STRUC
color                   GdkRGBA <>
_dx                     real4 ?
dy                      real4 ?
radius                  real4 ?
_GskShadow              ENDS
GskShadow               typedef _GskShadow

_GskParseLocation       STRUC
bytes                   gsize ?
chars                   gsize ?
lines                   gsize ?
line_bytes              gsize ?
line_chars              gsize ?
_GskParseLocation       ENDS
GskParseLocation        typedef _GskParseLocation


CALLBACK(GskParseErrorFunc, :ptr, :ptr, :ptr, :gpointer)

gsk_render_node_get_type proto
gsk_serialization_error_quark proto
gsk_render_node_ref proto :ptr
gsk_render_node_unref proto :ptr
gsk_render_node_get_node_type proto :ptr
gsk_render_node_get_bounds proto :ptr, :ptr
gsk_render_node_draw proto :ptr, :ptr
gsk_render_node_serialize proto :ptr
gsk_render_node_write_to_file proto :ptr, :ptr, :ptr
gsk_render_node_deserialize proto :ptr, :GskParseErrorFunc, :gpointer

define GSK_TYPE_DEBUG_NODE                     <gsk_debug_node_get_type>
define GSK_TYPE_COLOR_NODE                     <gsk_color_node_get_type>
define GSK_TYPE_TEXTURE_NODE                   <gsk_texture_node_get_type>
define GSK_TYPE_LINEAR_GRADIENT_NODE           <gsk_linear_gradient_node_get_type>
define GSK_TYPE_REPEATING_LINEAR_GRADIENT_NODE <gsk_repeating_linear_gradient_node_get_type>
define GSK_TYPE_RADIAL_GRADIENT_NODE           <gsk_radial_gradient_node_get_type>
define GSK_TYPE_REPEATING_RADIAL_GRADIENT_NODE <gsk_repeating_radial_gradient_node_get_type>
define GSK_TYPE_CONIC_GRADIENT_NODE            <gsk_conic_gradient_node_get_type>
define GSK_TYPE_BORDER_NODE                    <gsk_border_node_get_type>
define GSK_TYPE_INSET_SHADOW_NODE              <gsk_inset_shadow_node_get_type>
define GSK_TYPE_OUTSET_SHADOW_NODE             <gsk_outset_shadow_node_get_type>
define GSK_TYPE_CAIRO_NODE                     <gsk_cairo_node_get_type>
define GSK_TYPE_CONTAINER_NODE                 <gsk_container_node_get_type>
define GSK_TYPE_TRANSFORM_NODE                 <gsk_transform_node_get_type>
define GSK_TYPE_OPACITY_NODE                   <gsk_opacity_node_get_type>
define GSK_TYPE_COLOR_MATRIX_NODE              <gsk_color_matrix_node_get_type>
define GSK_TYPE_REPEAT_NODE                    <gsk_repeat_node_get_type>
define GSK_TYPE_CLIP_NODE                      <gsk_clip_node_get_type>
define GSK_TYPE_ROUNDED_CLIP_NODE              <gsk_rounded_clip_node_get_type>
define GSK_TYPE_SHADOW_NODE                    <gsk_shadow_node_get_type>
define GSK_TYPE_BLEND_NODE                     <gsk_blend_node_get_type>
define GSK_TYPE_CROSS_FADE_NODE                <gsk_cross_fade_node_get_type>
define GSK_TYPE_TEXT_NODE                      <gsk_text_node_get_type>
define GSK_TYPE_BLUR_NODE                      <gsk_blur_node_get_type>
define GSK_TYPE_GL_SHADER_NODE                 <gsk_gl_shader_node_get_type>

;GskDebugNode            typedef _GskDebugNode
;GskColorNode            typedef _GskColorNode
;GskTextureNode          typedef _GskTextureNode
;GskLinearGradientNode   typedef _GskLinearGradientNode
;GskRepeatingLinearGradientNode typedef _GskRepeatingLinearGradientNode
;GskRadialGradientNode   typedef _GskRadialGradientNode
;GskRepeatingRadialGradientNode typedef _GskRepeatingRadialGradientNode
;GskConicGradientNode    typedef _GskConicGradientNode
;GskBorderNode           typedef _GskBorderNode
;GskInsetShadowNode      typedef _GskInsetShadowNode
;GskOutsetShadowNode     typedef _GskOutsetShadowNode
;GskCairoNode            typedef _GskCairoNode
;GskContainerNode        typedef _GskContainerNode
;GskTransformNode        typedef _GskTransformNode
;GskOpacityNode          typedef _GskOpacityNode
;GskColorMatrixNode      typedef _GskColorMatrixNode
;GskRepeatNode           typedef _GskRepeatNode
;GskClipNode             typedef _GskClipNode
;GskRoundedClipNode      typedef _GskRoundedClipNode
;GskShadowNode           typedef _GskShadowNode
;GskBlendNode            typedef _GskBlendNode
;GskCrossFadeNode        typedef _GskCrossFadeNode
;GskTextNode             typedef _GskTextNode
;GskBlurNode             typedef _GskBlurNode
;GskGLShaderNode         typedef _GskGLShaderNode

gsk_debug_node_get_type proto
gsk_debug_node_new proto :ptr, :ptr
gsk_debug_node_get_child proto :ptr
gsk_debug_node_get_message proto :ptr

gsk_color_node_get_type proto
gsk_color_node_new proto :ptr, :ptr
gsk_color_node_get_color proto :ptr

gsk_texture_node_get_type proto
gsk_texture_node_new proto :ptr, :ptr
gsk_texture_node_get_texture proto :ptr

gsk_linear_gradient_node_get_type proto
gsk_linear_gradient_node_new proto :ptr, :ptr, :ptr, :ptr, :gsize
gsk_linear_gradient_node_get_start proto :ptr
gsk_linear_gradient_node_get_end proto :ptr
gsk_linear_gradient_node_get_n_color_stops proto :ptr
gsk_linear_gradient_node_get_color_stops proto :ptr, :ptr

gsk_repeating_linear_gradient_node_get_type proto
gsk_repeating_linear_gradient_node_new proto :ptr, :ptr, :ptr, :ptr, :gsize

gsk_conic_gradient_node_get_type proto
gsk_conic_gradient_node_new proto :ptr, :ptr, :real4, :ptr, :gsize
gsk_conic_gradient_node_get_center proto :ptr
gsk_conic_gradient_node_get_rotation proto :ptr
gsk_conic_gradient_node_get_angle proto :ptr
gsk_conic_gradient_node_get_n_color_stops proto :ptr
gsk_conic_gradient_node_get_color_stops proto :ptr, :ptr

gsk_radial_gradient_node_get_type proto
gsk_radial_gradient_node_new proto :ptr, :ptr, :real4, :real4, :real4, :real4, :ptr, :gsize
gsk_radial_gradient_node_get_n_color_stops proto :ptr
gsk_radial_gradient_node_get_color_stops proto :ptr, :ptr
gsk_radial_gradient_node_get_center proto :ptr
gsk_radial_gradient_node_get_hradius proto :ptr
gsk_radial_gradient_node_get_vradius proto :ptr
gsk_radial_gradient_node_get_start proto :ptr
gsk_radial_gradient_node_get_end proto :ptr

gsk_repeating_radial_gradient_node_get_type proto
gsk_repeating_radial_gradient_node_new proto :ptr, :ptr, :real4, :real4, :real4, :real4, :ptr, :gsize

gsk_border_node_get_type proto
gsk_border_node_new proto :ptr, :real4, :real4 ;:border_width, :border_color
gsk_border_node_get_outline proto :ptr
gsk_border_node_get_widths proto :ptr
gsk_border_node_get_colors proto :ptr

gsk_inset_shadow_node_get_type proto
gsk_inset_shadow_node_new proto :ptr, :ptr, :real4, :real4, :real4, :real4
gsk_inset_shadow_node_get_outline proto :ptr
gsk_inset_shadow_node_get_color proto :ptr
gsk_inset_shadow_node_get_dx proto :ptr
gsk_inset_shadow_node_get_dy proto :ptr
gsk_inset_shadow_node_get_spread proto :ptr
gsk_inset_shadow_node_get_blur_radius proto :ptr

gsk_outset_shadow_node_get_type proto
gsk_outset_shadow_node_new proto :ptr, :ptr, :real4, :real4, :real4, :real4
gsk_outset_shadow_node_get_outline proto :ptr
gsk_outset_shadow_node_get_color proto :ptr
gsk_outset_shadow_node_get_dx proto :ptr
gsk_outset_shadow_node_get_dy proto :ptr
gsk_outset_shadow_node_get_spread proto :ptr
gsk_outset_shadow_node_get_blur_radius proto :ptr

gsk_cairo_node_get_type proto
gsk_cairo_node_new proto :ptr
gsk_cairo_node_get_draw_context proto :ptr
gsk_cairo_node_get_surface proto :ptr

gsk_container_node_get_type proto
gsk_container_node_new proto :ptr, :guint
gsk_container_node_get_n_children proto :ptr
gsk_container_node_get_child proto :ptr, :guint

gsk_transform_node_get_type proto
gsk_transform_node_new proto :ptr, :ptr
gsk_transform_node_get_child proto :ptr
gsk_transform_node_get_transform proto :ptr

gsk_opacity_node_get_type proto
gsk_opacity_node_new proto :ptr, :real4
gsk_opacity_node_get_child proto :ptr
gsk_opacity_node_get_opacity proto :ptr

gsk_color_matrix_node_get_type proto
gsk_color_matrix_node_new proto :ptr, :ptr, :ptr
gsk_color_matrix_node_get_child proto :ptr
gsk_color_matrix_node_get_color_matrix proto :ptr
gsk_color_matrix_node_get_color_offset proto :ptr

gsk_repeat_node_get_type proto
gsk_repeat_node_new proto :ptr, :ptr, :ptr
gsk_repeat_node_get_child proto :ptr
gsk_repeat_node_get_child_bounds proto :ptr

gsk_clip_node_get_type proto
gsk_clip_node_new proto :ptr, :ptr
gsk_clip_node_get_child proto :ptr
gsk_clip_node_get_clip proto :ptr

gsk_rounded_clip_node_get_type proto
gsk_rounded_clip_node_new proto :ptr, :ptr
gsk_rounded_clip_node_get_child proto :ptr
gsk_rounded_clip_node_get_clip proto :ptr

gsk_shadow_node_get_type proto
gsk_shadow_node_new proto :ptr, :ptr, :gsize
gsk_shadow_node_get_child proto :ptr
gsk_shadow_node_get_shadow proto :ptr, :gsize
gsk_shadow_node_get_n_shadows proto :ptr

gsk_blend_node_get_type proto
gsk_blend_node_new proto :ptr, :ptr, :GskBlendMode
gsk_blend_node_get_bottom_child proto :ptr
gsk_blend_node_get_top_child proto :ptr
gsk_blend_node_get_blend_mode proto :ptr

gsk_cross_fade_node_get_type proto
gsk_cross_fade_node_new proto :ptr, :ptr, :real4
gsk_cross_fade_node_get_start_child proto :ptr
gsk_cross_fade_node_get_end_child proto :ptr
gsk_cross_fade_node_get_progress proto :ptr

gsk_text_node_get_type proto
gsk_text_node_new proto :ptr, :ptr, :ptr, :ptr
gsk_text_node_get_font proto :ptr
gsk_text_node_has_color_glyphs proto :ptr
gsk_text_node_get_num_glyphs proto :ptr
gsk_text_node_get_glyphs proto :ptr, :ptr
gsk_text_node_get_color proto :ptr
gsk_text_node_get_offset proto :ptr

gsk_blur_node_get_type proto
gsk_blur_node_new proto :ptr, :real4
gsk_blur_node_get_child proto :ptr
gsk_blur_node_get_radius proto :ptr

gsk_gl_shader_node_get_type proto
gsk_gl_shader_node_new proto :ptr, :ptr, :ptr, :ptr, :guint
gsk_gl_shader_node_get_n_children proto :ptr
gsk_gl_shader_node_get_child proto :ptr, :guint
gsk_gl_shader_node_get_args proto :ptr
gsk_gl_shader_node_get_shader proto :ptr


GSK_VALUE_HOLDS_RENDER_NODE macro value
  exitm<(G_VALUE_HOLDS ((value), GSK_TYPE_RENDER_NODE))>
  endm

gsk_value_set_render_node proto :ptr, :ptr
gsk_value_take_render_node proto :ptr, :ptr
gsk_value_get_render_node proto :ptr
gsk_value_dup_render_node proto :ptr

endif

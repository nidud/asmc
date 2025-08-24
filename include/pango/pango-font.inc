ifndef __PANGO_FONT_H__
define __PANGO_FONT_H__

include pango/pango-coverage.inc
include pango/pango-types.inc

include glib-object.inc
;include hb.inc

.enum PangoStyle {
  PANGO_STYLE_NORMAL,
  PANGO_STYLE_OBLIQUE,
  PANGO_STYLE_ITALIC
}

.enum PangoVariant {
  PANGO_VARIANT_NORMAL,
  PANGO_VARIANT_SMALL_CAPS,
  PANGO_VARIANT_ALL_SMALL_CAPS,
  PANGO_VARIANT_PETITE_CAPS,
  PANGO_VARIANT_ALL_PETITE_CAPS,
  PANGO_VARIANT_UNICASE,
  PANGO_VARIANT_TITLE_CAPS
}

.enum PangoWeight {
  PANGO_WEIGHT_THIN = 100,
  PANGO_WEIGHT_ULTRALIGHT = 200,
  PANGO_WEIGHT_LIGHT = 300,
  PANGO_WEIGHT_SEMILIGHT = 350,
  PANGO_WEIGHT_BOOK = 380,
  PANGO_WEIGHT_NORMAL = 400,
  PANGO_WEIGHT_MEDIUM = 500,
  PANGO_WEIGHT_SEMIBOLD = 600,
  PANGO_WEIGHT_BOLD = 700,
  PANGO_WEIGHT_ULTRABOLD = 800,
  PANGO_WEIGHT_HEAVY = 900,
  PANGO_WEIGHT_ULTRAHEAVY = 1000
}


.enum PangoStretch {
  PANGO_STRETCH_ULTRA_CONDENSED,
  PANGO_STRETCH_EXTRA_CONDENSED,
  PANGO_STRETCH_CONDENSED,
  PANGO_STRETCH_SEMI_CONDENSED,
  PANGO_STRETCH_NORMAL,
  PANGO_STRETCH_SEMI_EXPANDED,
  PANGO_STRETCH_EXPANDED,
  PANGO_STRETCH_EXTRA_EXPANDED,
  PANGO_STRETCH_ULTRA_EXPANDED
}


.enum PangoFontMask {
  PANGO_FONT_MASK_FAMILY  = 1 shl 0,
  PANGO_FONT_MASK_STYLE	  = 1 shl 1,
  PANGO_FONT_MASK_VARIANT = 1 shl 2,
  PANGO_FONT_MASK_WEIGHT  = 1 shl 3,
  PANGO_FONT_MASK_STRETCH = 1 shl 4,
  PANGO_FONT_MASK_SIZE	  = 1 shl 5,
  PANGO_FONT_MASK_GRAVITY = 1 shl 6,
  PANGO_FONT_MASK_VARIATIONS = 1 shl 7,
}


define PANGO_SCALE_XX_SMALL (0.5787037037037)
define PANGO_SCALE_X_SMALL  (0.6944444444444)
define PANGO_SCALE_SMALL    (0.8333333333333)
define PANGO_SCALE_MEDIUM   (1.0)
define PANGO_SCALE_LARGE    (1.2)
define PANGO_SCALE_X_LARGE  (1.44)
define PANGO_SCALE_XX_LARGE (1.728)

define PANGO_TYPE_FONT_DESCRIPTION <pango_font_description_get_type ()>

pango_font_description_get_type proto
pango_font_description_new proto
pango_font_description_copy proto :ptr
pango_font_description_copy_static proto :ptr
pango_font_description_hash proto :ptr
pango_font_description_equal proto :ptr, :ptr
pango_font_description_free proto :ptr
pango_font_descriptions_free proto :ptr, :sdword

pango_font_description_set_family proto :ptr, :ptr
pango_font_description_set_family_static proto :ptr, :ptr
pango_font_description_get_family proto :ptr
pango_font_description_set_style proto :ptr, :PangoStyle
pango_font_description_get_style proto :ptr
pango_font_description_set_variant proto :ptr, :PangoVariant
pango_font_description_get_variant proto :ptr
pango_font_description_set_weight proto :ptr, :PangoWeight
pango_font_description_get_weight proto :ptr
pango_font_description_set_stretch proto :ptr, :PangoStretch
pango_font_description_get_stretch proto :ptr
pango_font_description_set_size proto :ptr, :gint
pango_font_description_get_size proto :ptr
pango_font_description_set_absolute_size proto :ptr, :real8
pango_font_description_get_size_is_absolute proto :ptr
pango_font_description_set_gravity proto :ptr, :PangoGravity
pango_font_description_get_gravity proto :ptr

pango_font_description_set_variations_static proto :ptr, :ptr
pango_font_description_set_variations proto :ptr, :ptr
pango_font_description_get_variations proto :ptr

pango_font_description_get_set_fields proto :ptr
pango_font_description_unset_fields proto :ptr, :PangoFontMask

pango_font_description_merge proto :ptr, :ptr, :gboolean
pango_font_description_merge_static proto :ptr, :ptr, :gboolean

pango_font_description_better_match proto :ptr, :ptr, :ptr

pango_font_description_from_string proto :ptr
pango_font_description_to_string proto :ptr
pango_font_description_to_filename proto :ptr


define PANGO_TYPE_FONT_METRICS	<pango_font_metrics_get_type ()>

PangoFontMetrics	struct
ref_count		guint ?
ascent			sdword ?
descent			sdword ?
height			sdword ?
approximate_char_width	sdword ?
approximate_digit_width sdword ?
underline_position	sdword ?
underline_thickness	sdword ?
strikethrough_position	sdword ?
strikethrough_thickness sdword ?
PangoFontMetrics	ends

pango_font_metrics_get_type proto
pango_font_metrics_ref proto :ptr
pango_font_metrics_unref proto :ptr
pango_font_metrics_get_ascent proto :ptr
pango_font_metrics_get_descent proto :ptr
pango_font_metrics_get_height proto :ptr
pango_font_metrics_get_approximate_char_width proto :ptr
pango_font_metrics_get_approximate_digit_width proto :ptr
pango_font_metrics_get_underline_position proto :ptr
pango_font_metrics_get_underline_thickness proto :ptr
pango_font_metrics_get_strikethrough_position proto :ptr
pango_font_metrics_get_strikethrough_thickness proto :ptr

define PANGO_TYPE_FONT_FAMILY		   <pango_font_family_get_type ()>
PANGO_FONT_FAMILY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONT_FAMILY, PangoFontFamily))>
  endm
PANGO_IS_FONT_FAMILY macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONT_FAMILY))>
  endm
PANGO_FONT_FAMILY_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONT_FAMILY, PangoFontFamilyClass))>
  endm
PANGO_IS_FONT_FAMILY_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONT_FAMILY))>
  endm
PANGO_FONT_FAMILY_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONT_FAMILY, PangoFontFamilyClass))>
  endm

ifndef PANGO_DISABLE_DEPRECATED

PangoFontFamily		struct
parent_instance		GObject <>
PangoFontFamily		ends

PangoFontFamilyClass	struct
parent_class		GObjectClass <>
list_faces		proc :ptr, :ptr, :ptr
get_name		proc :ptr
is_monospace		proc :ptr
is_variable		proc :ptr
get_face		proc :ptr, :ptr
_pango_reserved2	proc
PangoFontFamilyClass	ends

endif

pango_font_family_get_type proto
pango_font_family_list_faces proto :ptr, :ptr, :ptr
pango_font_family_get_name proto :ptr
pango_font_family_is_monospace proto :ptr
pango_font_family_is_variable proto :ptr
pango_font_family_get_face proto :ptr, :ptr

define PANGO_TYPE_FONT_FACE <pango_font_face_get_type ()>
PANGO_FONT_FACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONT_FACE, PangoFontFace))>
  endm
PANGO_IS_FONT_FACE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONT_FACE))>
  endm
PANGO_FONT_FACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONT_FACE, PangoFontFaceClass))>
  endm
PANGO_IS_FONT_FACE_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONT_FACE))>
  endm
PANGO_FONT_FACE_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONT_FACE, PangoFontFaceClass))>
  endm

ifndef PANGO_DISABLE_DEPRECATED

PangoFontFace		struct
parent_instance		GObject <>
PangoFontFace		ends

PangoFontFaceClass	struct
parent_class		GObjectClass <>
get_face_name		proc :ptr
describe		proc :ptr
list_sizes		proc :ptr, :ptr, :ptr
is_synthesized		proc :ptr
get_family		proc :ptr
_pango_reserved3	proc
_pango_reserved4	proc
PangoFontFaceClass	ends

endif

pango_font_face_get_type proto

pango_font_face_describe proto :ptr
pango_font_face_get_face_name proto :ptr
pango_font_face_list_sizes proto :ptr, :ptr, :ptr
pango_font_face_is_synthesized proto :ptr

pango_font_face_get_family proto :ptr

define PANGO_TYPE_FONT	<pango_font_get_type ()>
PANGO_FONT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONT, PangoFont))>
  endm
PANGO_IS_FONT macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONT))>
  endm
PANGO_FONT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONT, PangoFontClass))>
  endm
PANGO_IS_FONT_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONT))>
  endm
PANGO_FONT_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONT, PangoFontClass))>
  endm


ifndef PANGO_DISABLE_DEPRECATED

PangoFont		struct
parent_instance		GObject <>
PangoFont		ends

PangoFontClass		struct
parent_class		GObjectClass <>
describe		proc :ptr
get_coverage		proc :ptr, :ptr
get_glyph_extents	proc :ptr, :PangoGlyph, :ptr, :ptr
get_metrics		proc :ptr, :ptr
get_font_map		proc :ptr
describe_absolute	proc :ptr
get_features		proc :ptr, :ptr, :guint, :ptr
create_hb_font		proc :ptr
PangoFontClass		ends

endif

pango_font_get_type proto

pango_font_describe proto :ptr
pango_font_describe_with_absolute_size proto :ptr
pango_font_get_coverage proto :ptr, :ptr
ifndef __GI_SCANNER__
pango_font_find_shaper proto :ptr, :ptr, :guint32
endif
pango_font_get_metrics proto :ptr, :ptr
pango_font_get_glyph_extents proto :ptr, :PangoGlyph, :ptr, :ptr
pango_font_get_font_map proto :ptr

pango_font_get_face proto :ptr

pango_font_has_char proto :ptr, :gunichar
pango_font_get_features proto :ptr, :ptr, :guint, :ptr
pango_font_get_hb_font proto :ptr

pango_font_get_languages proto :ptr

pango_font_serialize proto :ptr

pango_font_deserialize proto :ptr, :ptr, :ptr

define PANGO_GLYPH_EMPTY	   (0x0FFFFFFF)
define PANGO_GLYPH_INVALID_INPUT   (0xFFFFFFFF)
define PANGO_GLYPH_UNKNOWN_FLAG	   (0x10000000)
PANGO_GET_UNKNOWN_GLYPH macro wc
  exitm<((wc) or PANGO_GLYPH_UNKNOWN_FLAG)>
  endm

ifndef __GI_SCANNER__
ifndef PANGO_DISABLE_DEPRECATED
define PANGO_UNKNOWN_GLYPH_WIDTH  10
define PANGO_UNKNOWN_GLYPH_HEIGHT 14
endif
endif

endif

ifndef __PANGO_ATTRIBUTES_H__
define __PANGO_ATTRIBUTES_H__

include pango/pango-font.inc
include pango/pango-color.inc
include glib-object.inc

.enum PangoAttrType {
  PANGO_ATTR_INVALID,
  PANGO_ATTR_LANGUAGE,
  PANGO_ATTR_FAMILY,
  PANGO_ATTR_STYLE,
  PANGO_ATTR_WEIGHT,
  PANGO_ATTR_VARIANT,
  PANGO_ATTR_STRETCH,
  PANGO_ATTR_SIZE,
  PANGO_ATTR_FONT_DESC,
  PANGO_ATTR_FOREGROUND,
  PANGO_ATTR_BACKGROUND,
  PANGO_ATTR_UNDERLINE,
  PANGO_ATTR_STRIKETHROUGH,
  PANGO_ATTR_RISE,
  PANGO_ATTR_SHAPE,
  PANGO_ATTR_SCALE,
  PANGO_ATTR_FALLBACK,
  PANGO_ATTR_LETTER_SPACING,
  PANGO_ATTR_UNDERLINE_COLOR,
  PANGO_ATTR_STRIKETHROUGH_COLOR,
  PANGO_ATTR_ABSOLUTE_SIZE,
  PANGO_ATTR_GRAVITY,
  PANGO_ATTR_GRAVITY_HINT,
  PANGO_ATTR_FONT_FEATURES,
  PANGO_ATTR_FOREGROUND_ALPHA,
  PANGO_ATTR_BACKGROUND_ALPHA,
  PANGO_ATTR_ALLOW_BREAKS,
  PANGO_ATTR_SHOW,
  PANGO_ATTR_INSERT_HYPHENS,
  PANGO_ATTR_OVERLINE,
  PANGO_ATTR_OVERLINE_COLOR,
  PANGO_ATTR_LINE_HEIGHT,
  PANGO_ATTR_ABSOLUTE_LINE_HEIGHT,
  PANGO_ATTR_TEXT_TRANSFORM,
  PANGO_ATTR_WORD,
  PANGO_ATTR_SENTENCE,
  PANGO_ATTR_BASELINE_SHIFT,
  PANGO_ATTR_FONT_SCALE,
}


.enum PangoUnderline {
  PANGO_UNDERLINE_NONE,
  PANGO_UNDERLINE_SINGLE,
  PANGO_UNDERLINE_DOUBLE,
  PANGO_UNDERLINE_LOW,
  PANGO_UNDERLINE_ERROR,
  PANGO_UNDERLINE_SINGLE_LINE,
  PANGO_UNDERLINE_DOUBLE_LINE,
  PANGO_UNDERLINE_ERROR_LINE
}



.enum PangoOverline {
  PANGO_OVERLINE_NONE,
  PANGO_OVERLINE_SINGLE
}


.enum PangoShowFlags {
  PANGO_SHOW_NONE        = 0,
  PANGO_SHOW_SPACES      = 1 shl 0,
  PANGO_SHOW_LINE_BREAKS = 1 shl 1,
  PANGO_SHOW_IGNORABLES  = 1 shl 2
}


.enum PangoTextTransform {
  PANGO_TEXT_TRANSFORM_NONE,
  PANGO_TEXT_TRANSFORM_LOWERCASE,
  PANGO_TEXT_TRANSFORM_UPPERCASE,
  PANGO_TEXT_TRANSFORM_CAPITALIZE,
}


.enum PangoBaselineShift {
  PANGO_BASELINE_SHIFT_NONE,
  PANGO_BASELINE_SHIFT_SUPERSCRIPT,
  PANGO_BASELINE_SHIFT_SUBSCRIPT,
}


.enum PangoFontScale {
  PANGO_FONT_SCALE_NONE,
  PANGO_FONT_SCALE_SUPERSCRIPT,
  PANGO_FONT_SCALE_SUBSCRIPT,
  PANGO_FONT_SCALE_SMALL_CAPS,
}


define PANGO_ATTR_INDEX_FROM_TEXT_BEGINNING (0)
define PANGO_ATTR_INDEX_TO_TEXT_END ((G_MAXUINT + 0))


_PangoAttribute         struct
klass                   ptr PangoAttrClass ?
start_index             guint ?
end_index               guint ?
_PangoAttribute         ends
PangoAttribute          typedef _PangoAttribute

CALLBACK(PangoAttrFilterFunc, :ptr, :gpointer)
CALLBACK(PangoAttrDataCopyFunc, :gconstpointer)

_PangoAttrClass         struct
type                    PangoAttrType ?
copy                    proc :ptr
destroy                 proc :ptr
equal                   proc :ptr, :ptr
_PangoAttrClass         ends
PangoAttrClass          typedef _PangoAttrClass

_PangoAttrString        struct
attr                    PangoAttribute <>
value                   ptr sbyte ?
_PangoAttrString        ends
PangoAttrString         typedef _PangoAttrString

_PangoAttrLanguage      struct
attr                    PangoAttribute <>
value                   ptr PangoLanguage ?
_PangoAttrLanguage      ends
PangoAttrLanguage       typedef _PangoAttrLanguage

_PangoAttrInt           struct
attr                    PangoAttribute <>
value                   sdword ?
_PangoAttrInt           ends
PangoAttrInt            typedef _PangoAttrInt

_PangoAttrFloat         struct
attr                    PangoAttribute <>
value                   real8 ?
_PangoAttrFloat         ends
PangoAttrFloat          typedef _PangoAttrFloat

_PangoAttrColor         struct
attr                    PangoAttribute <>
color                   PangoColor <>
_PangoAttrColor         ends
PangoAttrColor          typedef _PangoAttrColor

_PangoAttrSize          struct
attr                    PangoAttribute <>
size                    sdword ?
RECORD
absolute                guint :  1 ?
ENDS
_PangoAttrSize          ends
PangoAttrSize           typedef _PangoAttrSize

_PangoAttrShape         struct
attr                    PangoAttribute <>
ink_rect                PangoRectangle <>
logical_rect            PangoRectangle <>
data                    gpointer ?
copy_func               PangoAttrDataCopyFunc ?
destroy_func            GDestroyNotify ?
_PangoAttrShape         ends
PangoAttrShape          typedef _PangoAttrShape


_PangoAttrFontDesc      struct
attr                    PangoAttribute <>
desc                    ptr PangoFontDescription ?
_PangoAttrFontDesc      ends
PangoAttrFontDesc       typedef _PangoAttrFontDesc


_PangoAttrFontFeatures  struct
attr                    PangoAttribute <>
features                ptr gchar ?
_PangoAttrFontFeatures  ends
PangoAttrFontFeatures   typedef _PangoAttrFontFeatures

pango_attribute_get_type proto

pango_attr_type_register proto :ptr
pango_attr_type_get_name proto :PangoAttrType
pango_attribute_init proto :ptr, :ptr
pango_attribute_copy proto :ptr
pango_attribute_destroy proto :ptr
pango_attribute_equal proto :ptr, :ptr

pango_attr_language_new proto :ptr
pango_attr_family_new proto :ptr
pango_attr_foreground_new proto :guint16, :guint16, :guint16
pango_attr_background_new proto :guint16, :guint16, :guint16
pango_attr_size_new proto :sdword
pango_attr_size_new_absolute proto :sdword
pango_attr_style_new proto :PangoStyle
pango_attr_weight_new proto :PangoWeight
pango_attr_variant_new proto :PangoVariant
pango_attr_stretch_new proto :PangoStretch
pango_attr_font_desc_new proto :ptr

pango_attr_underline_new proto :PangoUnderline
pango_attr_underline_color_new proto :guint16, :guint16, :guint16
pango_attr_strikethrough_new proto :gboolean
pango_attr_strikethrough_color_new proto :guint16, :guint16, :guint16
pango_attr_rise_new proto :sdword
pango_attr_baseline_shift_new proto :sdword
pango_attr_font_scale_new proto :PangoFontScale
pango_attr_scale_new proto :real8
pango_attr_fallback_new proto :gboolean
pango_attr_letter_spacing_new proto :sdword
pango_attr_shape_new proto :ptr, :ptr
pango_attr_shape_new_with_data proto :ptr, :ptr, :gpointer, :PangoAttrDataCopyFunc, :GDestroyNotify
pango_attr_gravity_new proto :PangoGravity
pango_attr_gravity_hint_new proto :PangoGravityHint
pango_attr_font_features_new proto :ptr
pango_attr_foreground_alpha_new proto :guint16
pango_attr_background_alpha_new proto :guint16
pango_attr_allow_breaks_new proto :gboolean

pango_attr_word_new proto
pango_attr_sentence_new proto

pango_attr_insert_hyphens_new proto :gboolean
pango_attr_overline_new proto :PangoOverline
pango_attr_overline_color_new proto :guint16, :guint16, :guint16
pango_attr_show_new proto :PangoShowFlags
pango_attr_line_height_new proto :real8
pango_attr_line_height_new_absolute proto :sdword
pango_attr_text_transform_new proto :PangoTextTransform

pango_attribute_as_string proto :ptr
pango_attribute_as_language proto :ptr
pango_attribute_as_int proto :ptr
pango_attribute_as_size proto :ptr
pango_attribute_as_float proto :ptr
pango_attribute_as_color proto :ptr
pango_attribute_as_font_desc proto :ptr
pango_attribute_as_shape proto :ptr
pango_attribute_as_font_features proto :ptr

;PangoAttrList           typedef _PangoAttrList
;PangoAttrIterator       typedef _PangoAttrIterator

define PANGO_TYPE_ATTR_LIST <pango_attr_list_get_type ()>

pango_attr_list_get_type proto

pango_attr_list_new proto
pango_attr_list_ref proto :ptr
pango_attr_list_unref proto :ptr
pango_attr_list_copy proto :ptr
pango_attr_list_insert proto :ptr, :ptr
pango_attr_list_insert_before proto :ptr, :ptr
pango_attr_list_change proto :ptr, :ptr
pango_attr_list_splice proto :ptr, :ptr, :sdword, :sdword
pango_attr_list_update proto :ptr, :sdword, :sdword, :sdword

pango_attr_list_filter proto :ptr, :PangoAttrFilterFunc, :gpointer
pango_attr_list_get_attributes proto :ptr
pango_attr_list_equal proto :ptr, :ptr

pango_attr_list_to_string proto :ptr
pango_attr_list_from_string proto :ptr

pango_attr_iterator_get_type proto

pango_attr_list_get_iterator proto :ptr

pango_attr_iterator_range proto :ptr, :ptr, :ptr
pango_attr_iterator_next proto :ptr
pango_attr_iterator_copy proto :ptr
pango_attr_iterator_destroy proto :ptr
pango_attr_iterator_get proto :ptr, :PangoAttrType
pango_attr_iterator_get_font proto :ptr, :ptr, :ptr, :ptr
pango_attr_iterator_get_attrs proto :ptr

endif

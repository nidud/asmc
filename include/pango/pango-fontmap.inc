ifndef __PANGO_FONTMAP_H__
define __PANGO_FONTMAP_H__

include pango/pango-types.inc
include pango/pango-font.inc
include pango/pango-fontset.inc

define PANGO_TYPE_FONT_MAP  <pango_font_map_get_type>
PANGO_FONT_MAP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONT_MAP, PangoFontMap))>
  endm
PANGO_IS_FONT_MAP macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONT_MAP))>
  endm
PANGO_FONT_MAP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONT_MAP, PangoFontMapClass))>
  endm
PANGO_IS_FONT_MAP_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONT_MAP))>
  endm
PANGO_FONT_MAP_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONT_MAP, PangoFontMapClass))>
  endm

_PangoFontMap           struct
parent_instance         GObject <>
_PangoFontMap           ends

_PangoFontMapClass      struct
parent_class            GObjectClass <>
load_font               proc :ptr, :ptr, :ptr
list_families           proc :ptr, :ptr, :ptr
load_fontset            proc :ptr, :ptr, :ptr, :ptr
shape_engine_type       ptr sbyte ?
get_serial              proc :ptr
changed                 proc :ptr
get_family              proc :ptr, :ptr
get_face                proc :ptr, :ptr
_PangoFontMapClass      ends
PangoFontMapClass       typedef _PangoFontMapClass

pango_font_map_get_type proto
pango_font_map_create_context proto :ptr
pango_font_map_load_font proto :ptr, :ptr, :ptr
pango_font_map_load_fontset proto :ptr, :ptr, :ptr, :ptr
pango_font_map_list_families proto :ptr, :ptr, :ptr
pango_font_map_get_serial proto :ptr
pango_font_map_changed proto :ptr
pango_font_map_get_family proto :ptr, :ptr

endif

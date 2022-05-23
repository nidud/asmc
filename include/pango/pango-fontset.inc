ifndef __PANGO_FONTSET_H__
define __PANGO_FONTSET_H__

include pango/pango-coverage.inc
include pango/pango-types.inc

include glib-object.inc

define PANGO_TYPE_FONTSET <pango_fontset_get_type>
PANGO_FONTSET macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONTSET, PangoFontset))>
  endm
PANGO_IS_FONTSET macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONTSET))>
  endm
PANGO_FONTSET_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), PANGO_TYPE_FONTSET, PangoFontsetClass))>
  endm
PANGO_IS_FONTSET_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), PANGO_TYPE_FONTSET))>
  endm
PANGO_FONTSET_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), PANGO_TYPE_FONTSET, PangoFontsetClass))>
  endm


pango_fontset_get_type proto

CALLBACK(PangoFontsetForeachFunc, :ptr, :ptr, :gpointer)

_PangoFontset           struct
parent_instance         GObject <>
_PangoFontset           ends
PangoFontset            typedef _PangoFontset


_PangoFontsetClass      struct
parent_class            GObjectClass <>
get_font                proc :ptr, :guint
get_metrics             proc :ptr
get_language            proc :ptr
foreach                 proc :ptr, :PangoFontsetForeachFunc, :gpointer
_pango_reserved1        proc
_pango_reserved2        proc
_pango_reserved3        proc
_pango_reserved4        proc
_PangoFontsetClass      ends
PangoFontsetClass       typedef _PangoFontsetClass

pango_fontset_get_font proto :ptr, :guint
pango_fontset_get_metrics proto :ptr
pango_fontset_foreach proto :ptr, :PangoFontsetForeachFunc, :gpointer

endif

ifndef __PANGO_FONTSET_SIMPLE_H__
define __PANGO_FONTSET_SIMPLE_H__

include pango/pango-coverage.inc
include pango/pango-types.inc
include pango/pango-fontset.inc

include glib-object.inc

define PANGO_TYPE_FONTSET_SIMPLE <pango_fontset_simple_get_type>
PANGO_FONTSET_SIMPLE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), PANGO_TYPE_FONTSET_SIMPLE, PangoFontsetSimple))>
  endm
PANGO_IS_FONTSET_SIMPLE macro object
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), PANGO_TYPE_FONTSET_SIMPLE))>
  endm

;PangoFontsetSimple      typedef _PangoFontsetSimple
;PangoFontsetSimpleClass typedef _PangoFontsetSimpleClass

pango_fontset_simple_get_type proto
pango_fontset_simple_new proto :ptr
pango_fontset_simple_append proto :ptr, :ptr
pango_fontset_simple_size proto :ptr

endif

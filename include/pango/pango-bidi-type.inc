ifndef __PANGO_BIDI_TYPE_H__
define __PANGO_BIDI_TYPE_H__

include glib.inc

include pango/pango-version-macros.inc
include pango/pango-direction.inc

ifndef PANGO_DISABLE_DEPRECATED

.enum PangoBidiType {
    PANGO_BIDI_TYPE_L,
    PANGO_BIDI_TYPE_LRE,
    PANGO_BIDI_TYPE_LRO,
    PANGO_BIDI_TYPE_R,
    PANGO_BIDI_TYPE_AL,
    PANGO_BIDI_TYPE_RLE,
    PANGO_BIDI_TYPE_RLO,
    PANGO_BIDI_TYPE_PDF,
    PANGO_BIDI_TYPE_EN,
    PANGO_BIDI_TYPE_ES,
    PANGO_BIDI_TYPE_ET,
    PANGO_BIDI_TYPE_AN,
    PANGO_BIDI_TYPE_CS,
    PANGO_BIDI_TYPE_NSM,
    PANGO_BIDI_TYPE_BN,
    PANGO_BIDI_TYPE_B,
    PANGO_BIDI_TYPE_S,
    PANGO_BIDI_TYPE_WS,
    PANGO_BIDI_TYPE_ON,
    PANGO_BIDI_TYPE_LRI,
    PANGO_BIDI_TYPE_RLI,
    PANGO_BIDI_TYPE_FSI,
    PANGO_BIDI_TYPE_PDI
    }

pango_bidi_type_for_unichar proto __cdecl :gunichar
pango_unichar_direction proto __cdecl :gunichar
pango_find_base_dir proto __cdecl :ptr, :gint
pango_get_mirror_char proto __cdecl :gunichar, :ptr

endif

endif

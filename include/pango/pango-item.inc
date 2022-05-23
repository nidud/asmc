ifndef __PANGO_ITEM_H__
define __PANGO_ITEM_H__

include pango/pango-types.inc
include pango/pango-attributes.inc

define PANGO_ANALYSIS_FLAG_CENTERED_BASELINE (1 shl 0)
define PANGO_ANALYSIS_FLAG_IS_ELLIPSIS (1 shl 1)
define PANGO_ANALYSIS_FLAG_NEED_HYPHEN (1 shl 2)

_PangoAnalysis          struct
ifndef __GI_SCANNER__
shape_engine            ptr PangoEngineShape ?
lang_engine             ptr PangoEngineLang ?
else
shape_engine            gpointer ?
lang_engine             gpointer ?
endif
font                    ptr PangoFont ?
level                   guint8 ?
gravity                 guint8 ?
flags                   guint8 ?
script                  guint8 ?
language                ptr PangoLanguage ?
extra_attrs             ptr GSList ?
_PangoAnalysis          ends
PangoAnalysis           typedef _PangoAnalysis


_PangoItem              struct
offs                    sdword ?
length                  sdword ?
num_chars               sdword ?
analysis                PangoAnalysis <>
_PangoItem              ends
PangoItem               typedef _PangoItem

define PANGO_TYPE_ITEM <pango_item_get_type>

pango_item_get_type proto
pango_item_new proto
pango_item_copy proto :ptr
pango_item_free proto :ptr
pango_item_split proto :ptr, :sdword, :sdword
pango_item_apply_attrs proto :ptr, :ptr
pango_reorder_items proto :ptr
pango_itemize proto :ptr, :ptr, :sdword, :sdword, :ptr, :ptr
pango_itemize_with_base_dir proto :ptr, :PangoDirection, :ptr, :sdword, :sdword, :ptr, :ptr

endif

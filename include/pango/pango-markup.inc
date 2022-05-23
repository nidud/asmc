ifndef __PANGO_MARKUP_H__
define __PANGO_MARKUP_H__

include pango/pango-attributes.inc

pango_markup_parser_new proto :gunichar
pango_markup_parser_finish proto :ptr, :ptr, :ptr, :ptr, :ptr
pango_parse_markup proto :ptr, :sdword, :gunichar, :ptr, :ptr, :ptr, :ptr

endif
